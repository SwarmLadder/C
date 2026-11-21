# Mastery lab I2 — Binary stream histogram

**Difficulty:** intermediate / I/O reliability. **Target:** count_stream_bytes. **Suggested time:** 75–120 minutes.

## Problem contract

Read all remaining bytes from a readable FILE* until normal EOF, then write 256 uint64_t counters indexed by the unsigned byte values 0 through 255. Count every byte, including zero bytes and high-bit bytes. The function does not own the stream and must not close it.

Return false for NULL arguments or a read error. Preserve the existing 256 output counters unless the stream reached normal EOF successfully. Use local temporary counters and publish them only after complete success.

## Correct stream reading

Use an unsigned char buffer and fread in blocks. Every returned byte value can index [0,256) safely. A short fread call must be interpreted: if ferror is true, the operation failed; otherwise normal EOF may have been reached. Use a count type large enough for the specified workload and reject counter increment overflow before incrementing.

The function must not use strlen: binary data can contain embedded zeros, and its size is determined by fread. Avoid accidental sign extension by storing read bytes as unsigned char.

## Worked fixtures

Input bytes 00 FF 00 0A 80 41 41 produce counts for 00=2, FF=1, 0A=1, 80=1 and 41=2, with all other counters zero. An empty file produces 256 zero counters. Pass NULL for the stream; the function must fail while preserving a sentinel counter array.

Use a temporary stream in your tests:

~~~c
FILE *f = tmpfile();
unsigned char bytes[] = {0, 255, 0};
fwrite(bytes, 1, sizeof bytes, f);
rewind(f);
/* Test count_stream_bytes(f, counters) here, then fclose(f). */
~~~

Run:

~~~sh
make mastery-check TASK=byte_histogram
~~~

## Variations

- Count the most common byte with deterministic tie-breaking.
- Report entropy using a platform math library, explaining the difference between mathematical entropy and byte count.
- Build a CLI that reads from stdin and prints an ASCII frequency report; test with redirected binary input.

**Proof prompt:** Why are counters not partially modified when I/O fails halfway through?

**Interview follow-up:** Why does fgetc return int rather than char? To represent all unsigned char byte values plus the EOF sentinel.