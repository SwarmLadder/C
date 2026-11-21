# Intermediate C

Begin after you can traverse arrays and C strings. Pay attention to ownership, output arguments, and whether an error may change caller state.

## Workshops

1. [Output parameters](output-parameters.md)
2. [Mutable buffers](mutable-buffers.md)
3. [Parsing fields](parsing-fields.md)
4. [Sorted tables](sorted-tables.md)
5. [Callbacks](callbacks.md)
6. [Streams](streams.md)

## Professional deep dives

The guided workshops introduce one core function at a time. These longer chapters develop the language rules, invariants, debugging, and systems-level reasoning needed to write professional C code. For each chapter, trace the example, implement the independent exercises, and explain failure behavior.

1. [Headers, linkage and API design](deep-dives/01_headers_linkage_and_apis.md)
2. [Vectors, realloc and failure guarantees](deep-dives/02_realloc_vectors_and_strong_failure_guarantees.md)
3. [Parsing untrusted input and streams](deep-dives/03_input_parsing_and_stream_contracts.md)
4. [Sorting, comparators and binary search](deep-dives/04_sorting_searching_and_comparator_contracts.md)
5. [Alignment, endian decoding and binary I/O](deep-dives/05_layout_endianness_and_binary_io.md)
6. [C macros, _Generic and opaque APIs](deep-dives/06_generic_interfaces_and_the_preprocessor.md)

## Projects

1. [Room bookings](projects/room_usage.md)
2. [Grade histogram](projects/grade_bins.md)
3. [Line-numbered transcript](projects/transcript.md)

## Level assessment

Run `make check LEVEL=intermediate` to check all 24 core exercises and three project implementations. For each workshop, complete its five independent exercises, answer the knowledge check, and show one new boundary-case test. For a project review, demonstrate the extension and explain one design choice using a concrete example.

## Further practice

Complete the [additional C mastery labs](../mastery/README.md) for this level. The independent mastery grader keeps the original workshop exercises unchanged.
