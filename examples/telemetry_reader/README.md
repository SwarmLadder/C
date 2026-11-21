# Reference project — a real binary telemetry CLI in ISO C17

This is a **working, multi-file example**, not merely a project specification. The production-inspired exercise is to ingest an entire binary stream of version-1 telemetry frames, validate them, and report deterministic counters without printing a partial summary when a malformed frame is discovered later.

The executable uses the separately compiled decoder in mastery/reference/frame_header.c and the documented FrameHeader contract in mastery/include/mastery.h. It intentionally avoids POSIX-only read or mmap APIs, so the implementation targets ISO C17 streams. The input is redirected from a file to stdin.

## Run from the repository root

~~~sh
make build/telemetry-inspector
./build/telemetry-inspector --help
python3 -c "import sys; sys.stdout.buffer.write(b'SL\x01\x00\x02\x00\x00\x00\x03abc')" > /tmp/swarmladder-frame.bin
./build/telemetry-inspector < /tmp/swarmladder-frame.bin
~~~

Expected summary:

~~~text
frames=1 payload_bytes=3
kind=2 frames=1
~~~

No command in the CLI itself executes external tools. The Python one-liner is solely a deterministic fixture generator on your own machine; it never requires privileged operations. In GitHub Actions, tests create input bytes directly with Python and invoke the compiled binary with controlled stdin.

## Wire format and validation

Every frame starts with exactly nine bytes: the ASCII magic SL, version 1, a two-byte big-endian kind, and a four-byte big-endian payload length. The maximum accepted payload length is 1 MiB. The next payload_length bytes are binary payload, not a C string. The loop continues until clean EOF **at a frame boundary**.

A trailing header shorter than nine bytes, an invalid magic/version, an excessive length, or a truncated payload makes the entire command fail. The program reports the problem to stderr and exits nonzero. It writes **no summary** when any input frame fails validation, even if earlier frames were valid.

## Architecture and correctness

- The protocol decoder returns a structured, validated header and preserves its output on failure.
- The CLI reads exactly nine header bytes, then consumes payload in small 4096-byte chunks, so it never needs to allocate a whole payload.
- A zero-initialized 65,536-element counter array covers all uint16_t kind values. Before allocation it checks whether the array byte count is representable on the target.
- Total frame count, per-kind count and total payload byte count are uint64_t. The code guards against overflow **before** incrementing.
- No output is written until the entire stream has been validated; the final summary is deterministic and ordered by ascending numeric kind.
- A successful fflush is checked because buffered output can fail after earlier writes appeared successful.

A complete transaction cannot guarantee that stdout remains unchanged on *output failure partway through printing*, because stdout itself may have no rollback support. The no-partial-output guarantee applies to **input validation failures**. This distinction matters when describing production APIs.

## Adversarial tests

Tests cover empty streams, multiple kinds, binary NUL and high-bit payload bytes, exact maximum-length payload, all truncated header lengths, missing payload bytes, invalid magic/version, excessive lengths, unknown command-line arguments and a valid frame followed by an invalid frame (which must leave stdout empty). Run:

~~~sh
make build/telemetry-inspector
python3 -m unittest tests.test_telemetry_cli -v
~~~

The test suite intentionally avoids relying on a fixed path under /tmp for correctness; fixture bytes are passed through subprocess input. It checks return code, stdout and selected error diagnostics.

## Reimplement the capstone yourself

The original [telemetry decoder specification](../../mastery/projects/01_telemetry_decoder.md) is still the student's exercise. Do not start by copying this reference. Start with a fresh project in another directory, implement protocol parsing and stream reading independently, and compare output against these acceptance tests only when you have a complete solution.

**Extensions:** per-kind payload byte totals, a streaming checksum, a version-2 dispatch table, a configurable maximum frame count, a controlled allocator for failure injection, and property testing of the encoder/decoder pair. Every extension requires a written resource limit and an explicit failure behavior.

## What this example does not guarantee

It does not interpret payload contents, authenticate data, guarantee media durability, provide cryptographic integrity, or prevent a user from feeding a very large number of valid frames (the size of the input governs runtime). It is a **teaching reference**, not a production security gateway.
