# C17 mastery labs — implementation, proof, regression tests

The original workshop track practices 81 individually graded functions across 18 guided lessons and 9 projects. These six additional labs are deeper contracts that combine safety, performance and error-path reasoning. Each has an editable starter, a separate reference, and tests compiled under strict C17 flags on **GCC and Clang**.

| Level | Lab | Real skill |
| --- | --- | --- |
| Basics | [Checked 32-bit addition](tasks/01_checked_add.md) | Avoid signed overflow and preserve outputs |
| Basics | [Strict decimal parser](tasks/02_parse_decimal.md) | Grammar, range checks and invalid input |
| Intermediate | [Dynamic text buffer](tasks/03_text_buffer.md) | Ownership, realloc, capacity and failure guarantees |
| Intermediate | [Binary stream histogram](tasks/04_byte_histogram.md) | File I/O, short reads, 256 byte values and error preservation |
| Advanced | [Nine-byte frame decoder](tasks/05_frame_header.md) | Portable protocol fields, bounds checks and endian order |
| Advanced | [Dependency ordering](tasks/06_topological.md) | Graph invariants, cycles and deterministic output |

## Setup and grading

~~~sh
make mastery-reference
make mastery-check TASK=checked_add
make mastery-check LEVEL=basics
make mastery-check TASK=topological
~~~

The reference command executes all six completed implementations. The student target compiles the unfinished starter files and runs the selected test. Tests deliberately fail until you implement the corresponding code. More than one task can be selected by level; omitted task and level run all six. In contrast, make check runs the original 81-function workshop suite.

Edit only the desired implementation in mastery/starter. The API contracts are in mastery/include/mastery.h. Run make mastery-check TASK=... after each change. Look at reference code **after** you have a working draft or a written explanation of where you are stuck.

## A serious completion standard

Passing checks is **necessary, not sufficient**. For each lab, submit:
1. A function contract including inputs, outputs, ownership, valid ranges and failure behavior.
2. A one-paragraph proof or invariant showing that memory and result state remain valid.
3. A time and auxiliary-space analysis (include dynamic growth and I/O cost).
4. At least three learner-written tests the provided suite does not already cover.
5. A sanitizer/diagnostic build log and one adversarial input explanation.

Use -O1 -g -fsanitize=address,undefined with supported GCC/Clang installations when debugging locally; CI uses UBSan instrumentation. Sanitizers cannot prove safety, but they provide valuable evidence. Never run untrusted C code without an appropriate isolated environment.

## Practical review questions

Why is an output parameter not modified on failure? Where does each pointer remain valid? Are size calculations checked before arithmetic? How does one corrupted/truncated record behave? Does the code still work if input is empty? Which properties are platform-dependent? What happens if malloc fails?

When you can defend every answer without reading the reference, move on to the [integrated capstones](projects/README.md) and [course assessment](../curriculum/ASSESSMENT.md).

**Important:** The C course is standalone. These exercises run natively on your own machine, not inside SwarmLadder Lab.