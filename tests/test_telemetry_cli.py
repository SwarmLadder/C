"""Functional black-box tests of the portable C17 telemetry reader."""
from __future__ import annotations
import struct
import subprocess
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EXECUTABLE = ROOT / "build" / "telemetry-inspector"

def frame(kind: int, payload: bytes, *, length: int | None = None) -> bytes:
    declared = len(payload) if length is None else length
    return b"SL\x01" + struct.pack(">HI", kind, declared) + payload

class TelemetryCLI(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        result = subprocess.run(["make", "build/telemetry-inspector"], cwd=ROOT,
                                capture_output=True, text=True, timeout=45)
        if result.returncode != 0:
            raise AssertionError("telemetry C build failed: " + result.stdout + result.stderr)

    def execute(self, payload: bytes, *args: str):
        return subprocess.run([str(EXECUTABLE), *args], input=payload,
                              capture_output=True, timeout=12)

    def test_empty_input(self):
        result = self.execute(b"")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.decode(), "frames=0 payload_bytes=0\n")

    def test_multiple_kinds_sorted_with_binary_payload(self):
        raw = frame(2, b"\x00\xff") + frame(1, b"abc") + frame(2, b"")
        result = self.execute(raw)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.decode(),
                         "frames=3 payload_bytes=5\nkind=1 frames=1\nkind=2 frames=2\n")

    def test_kind_boundaries_and_max_payload(self):
        raw = frame(0, b"") + frame(65535, b"x" * 1048576)
        result = self.execute(raw)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.decode(),
                         "frames=2 payload_bytes=1048576\n"
                         "kind=0 frames=1\nkind=65535 frames=1\n")

    def test_every_truncated_header_rejected(self):
        header = frame(2, b"")[:9]
        for n in range(1, 9):
            with self.subTest(header_bytes=n):
                result = self.execute(header[:n])
                self.assertNotEqual(result.returncode, 0)
                self.assertEqual(result.stdout, b"")
                self.assertIn(b"Truncated frame header", result.stderr)

    def test_invalid_magic_version_size(self):
        invalid = [
            b"XL\x01\x00\x01\x00\x00\x00\x00",
            b"SL\x02\x00\x01\x00\x00\x00\x00",
            frame(1, b"", length=1048577),
        ]
        for raw in invalid:
            with self.subTest(raw=raw):
                result = self.execute(raw)
                self.assertNotEqual(result.returncode, 0)
                self.assertEqual(result.stdout, b"")
                self.assertIn(b"Invalid frame header", result.stderr)

    def test_truncated_payload_and_no_partial_summary(self):
        truncated = frame(2, b"ab", length=5)
        for raw in (truncated, frame(1, b"hello") + truncated):
            with self.subTest(raw=raw):
                result = self.execute(raw)
                self.assertNotEqual(result.returncode, 0)
                self.assertEqual(result.stdout, b"")
                self.assertIn(b"Truncated frame payload", result.stderr)

    def test_tampered_version_after_valid_frame(self):
        raw = frame(1, b"x") + b"SL\x02\x00\x01\x00\x00\x00\x00"
        result = self.execute(raw)
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(result.stdout, b"")

    def test_explicit_help_and_usage(self):
        help_result = self.execute(b"", "--help")
        self.assertEqual(help_result.returncode, 0)
        self.assertIn(b"Usage: telemetry-inspector", help_result.stdout)
        wrong_args = self.execute(b"", "foo")
        self.assertEqual(wrong_args.returncode, 2)
        self.assertEqual(wrong_args.stdout, b"")
        self.assertIn(b"Usage", wrong_args.stderr)

if __name__ == "__main__":
    unittest.main()
