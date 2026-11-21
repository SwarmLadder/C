# Basics C

Start here. Read the first function signature aloud, trace a sample input by hand, then change the function body and run its focused test.

## Workshops

1. [Clocks and units](clocks-and-units.md)
2. [Branches and boundaries](branches-and-boundaries.md)
3. [Loop invariants](loop-invariants.md)
4. [Sequences and windows](sequences-and-windows.md)
5. [Characters and text](characters-and-text.md)
6. [Records and reports](records-and-reports.md)

## Professional deep dives

The guided workshops introduce one core function at a time. These longer chapters develop the language rules, invariants, debugging, and systems-level reasoning needed to write professional C code. For each chapter, trace the example, implement the independent exercises, and explain failure behavior.

1. [Toolchain, translation units and linking](deep-dives/01_compilation_linkage_and_make.md)
2. [Integer conversions and overflow](deep-dives/02_integer_rules_and_checked_arithmetic.md)
3. [Object lifetime and pointer ownership](deep-dives/03_storage_lifetime_and_pointer_ownership.md)
4. [Array decay and pointer bounds](deep-dives/04_arrays_pointers_and_invariants.md)
5. [C strings and byte buffers](deep-dives/05_strings_bytes_and_text.md)
6. [Debugging, sanitizers and regression tests](deep-dives/06_debugging_and_reliable_tests.md)

## Projects

1. [Trail report](projects/trail_report.md)
2. [Meter invoice](projects/meter_bill.md)
3. [Reading streak](projects/reading_streak.md)

## Level assessment

Run `make check LEVEL=basics` to check all 24 core exercises and three project implementations. For each workshop, complete its five independent exercises, answer the knowledge check, and show one new boundary-case test. For a project review, demonstrate the extension and explain one design choice using a concrete example.

## Further practice

Complete the [additional C mastery labs](../mastery/README.md) for this level. The independent mastery grader keeps the original workshop exercises unchanged.
