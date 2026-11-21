# Capstone 01 — Telemetry frame decoder

**Estimated duration:** 8–12 hours across two weeks. **Target:** portable C17 CLI reading a binary stream, validating records and reporting clean summaries. **Related labs:** frame_header, byte_histogram, parse_decimal.

## Product requirements

Input consists of a sequence of nine-byte SL frame headers followed by payload data of the declared size. Version is exactly 1; kind is unsigned big-endian 16; length is unsigned big-endian 32 and no more than 1 MiB. Choose a consistent treatment for zero-length payloads. Report counts grouped by kind and the total payload bytes. Reject invalid magic, truncated headers/payloads, unsupported versions, oversized frames, and stream errors with nonzero exit status and a clear diagnostic on stderr.

Do not serialize or deserialize wire data by casting to a native struct pointer. Bytes are the protocol; struct layout is not.

## Architecture to design

Separate reader.c (bounded FILE* reads and short-read detection), protocol.c (pure byte decoder with no I/O), summary.c (dynamic/ordered counts), and main.c (CLI and exit codes). Provide matching headers with ownership contracts. The parser should stage a decoded frame before updating the summary. If updating a summary can fail due to allocation, decide whether the entire operation is atomic or whether partial summary output is allowed; document the choice.

Cap maximum memory use independently from frame length. For each record, read or skip payload in bounded blocks rather than allocating a buffer of declared length when content is not otherwise needed.

## Acceptance tests you write

1. Empty input produces a documented zero-record summary and success.
2. One valid header plus payload yields one count and the exact byte total.
3. Two different kinds yield deterministic sorted output regardless of input order.
4. Truncate at every header offset 1–8 and verify failure, not a crash.
5. Declare length 100 but supply 99 bytes; reject.
6. Change version or magic; reject without publishing a completed frame.
7. Use a zero payload and an exactly 1 MiB payload; verify upper bound.
8. Feed bytes including 0x00 and 0xff; never use strlen on payload bytes.
9. Exercise a failed input open and a failed output write where feasible.
10. Run representative malformed inputs under sanitizers.

## Engineering questions

Where do allocations happen? Which module owns each object? Does a decoding error leave the output header unchanged? Are all 16/32-bit shifts performed on unsigned values of sufficient width? Is the CLI deterministic on repeated runs? Why does fclose success matter for buffered output?

## Stretch work

Add a simple checksum with a fully documented polynomial and example, or support version 2 through an explicit dispatch table. Fuzz the parser with deterministic random lengths and bytes, comparing it against a small independently written Python oracle.

**Review gate:** Pass the acceptance tests and demonstrate a safe failure on a truncated payload while the error code and memory state remain correct.