# Advanced C

Begin after you can use pointers, structs and file streams. Draw the ownership or data layout for each task and check boundary cases before coding.

## Workshops

1. [Allocation and ownership](allocation-and-ownership.md)
2. [Linked structures](linked-structures.md)
3. [Binary records](binary-records.md)
4. [Circular queues](circular-queues.md)
5. [Bit sets](bit-sets.md)
6. [Transactional updates](transactional-updates.md)

## Professional deep dives

The guided workshops introduce one core function at a time. These longer chapters develop the language rules, invariants, debugging, and systems-level reasoning needed to write professional C code. For each chapter, trace the example, implement the independent exercises, and explain failure behavior.

1. [Undefined behavior and optimization](deep-dives/01_undefined_behavior_and_optimization.md)
2. [Data races, atomics and memory ordering](deep-dives/02_c11_threads_and_atomics.md)
3. [POSIX I/O and durability boundaries](deep-dives/03_posix_io_and_reliability.md)
4. [Queues, hash tables and layout tradeoffs](deep-dives/04_hash_tables_queues_and_representation.md)
5. [Security, fuzzing and parser hardening](deep-dives/05_security_fuzzing_and_parser_hardening.md)
6. [Profiling, benchmarking and portability](deep-dives/06_profiling_optimization_and_portability.md)

## Projects

1. [Telemetry frame index](projects/inspect_capture.md)
2. [Event replay](projects/replay_recent.md)
3. [Inventory audit](projects/audit_stock.md)

## Level assessment

Run `make check LEVEL=advanced` to check all 24 core exercises and three project implementations. For each workshop, complete its five independent exercises, answer the knowledge check, and show one new boundary-case test. For a project review, demonstrate the extension and explain one design choice using a concrete example.

## Further practice

Complete the [additional C mastery labs](../mastery/README.md) for this level. The independent mastery grader keeps the original workshop exercises unchanged.
