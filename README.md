# SwarmLadder C — Fundamentals to systems programming

A standalone, substantial **C17 course** focused on real compilation, memory ownership, robust APIs, debugging, algorithms and systems engineering. Learn the rules, prove invariants and build programs that survive invalid inputs, not just programs that print expected values.

## Curriculum

| Level | Guided workshops | Professional deep dives | Emphasis |
| --- | --- | --- | --- |
| [Foundations](basics/README.md) | 6 | 6 | C toolchain, integer rules, arrays, strings, lifetime and debugging |
| [Intermediate](intermediate/README.md) | 6 | 6 | API design, allocation, parsing, sorting, binary I/O and macros |
| [Advanced](advanced/README.md) | 6 | 6 | Undefined behavior, atomics, POSIX, data structures, security and performance |

**36 core lessons in total:** 18 existing function-focused workshops plus 18 new in-depth technical chapters. In addition: 81 existing graded functions (72 core functions and 9 project implementations), 12 graded mastery labs, 90 independent exercises, 9 projects, and 3 larger capstone project specifications.

## Getting started

Requires a C17-compatible GCC or Clang compiler and Make.

~~~sh
git clone https://github.com/SwarmLadder/C.git
cd C
make reference
make check TASK=whole_minutes
~~~

The student starter deliberately fails until you implement it. Read [Clocks and units](basics/clocks-and-units.md), edit basics/starter/clocks-and-units.c and rerun the focused check. Check an entire level with the following:

~~~sh
make check LEVEL=basics
~~~

## Twelve graded systems labs

Read the [mastery lab guide](mastery/README.md). Start from mastery/starter and compare against mastery/reference **only after** attempting each problem.

~~~sh
make mastery-reference
make mastery-check TASK=checked_add
make mastery-check TASK=parse_decimal
make mastery-check TASK=text_buffer
make mastery-check TASK=byte_histogram
make mastery-check TASK=frame_header
make mastery-check TASK=topological
make mastery-check TASK=reverse_span
make mastery-check TASK=parse_hex
make mastery-check TASK=lower_bound
make mastery-check TASK=unique_sorted
make mastery-check TASK=ring_queue
make mastery-check TASK=dag_distances
~~~

Each command compiles all C17 source files with strict warnings, then runs the selected task. The reference command validates the worked solutions; the student commands fail until the relevant starter is implemented.

## How to reach professional competence

Follow the [12-week learning roadmap](curriculum/ROADMAP.md), use the [C interview workbook](curriculum/INTERVIEW.md), and measure skills with the [assessment rubric](curriculum/ASSESSMENT.md). Integrate language skills in the [three larger capstone specifications](mastery/projects/README.md).

The cycle is **read → trace → implement → test edge cases → debug → prove correctness → improve complexity → solve a variation**. Maintain a bug journal and record every ownership decision. Work through both the workshop and deep-dive tracks at each level before attempting its capstone.

## Reliability and portability

GitHub Actions compiles the original and new student/reference code under GCC and Clang, runs both reference test suites with undefined-behavior instrumentation, and checks course completeness. The new reference labs have explicit failure-preservation and boundary checks.

The executable exercises target **ISO C17**. Selected advanced chapters explain optional C11 atomics and platform-specific POSIX APIs; those examples are labeled accordingly. A passing compiler test or sanitizer run is not formal proof of memory safety.

A pointer paired with zero length may be null when no elements are accessed. Otherwise follow the API's documented object-size, aliasing, initialization, ownership and error contracts. The standard workshop API is in include/course.h; the 12 mastery exercises have their own header at mastery/include/mastery.h.

**Platform status:** Standalone repository only. Not integrated into SwarmLadder Lab.

## New practice materials

The expanded mastery track includes **12 fully tested lab contracts** in [mastery/README.md](mastery/README.md), with a separate unfinished starter and completed reference implementation for each. You can now practice in-place byte transformations, strict hex parsing, binary search, stable deduplication, circular queues, and DAG shortest paths in addition to the original six.

Go beyond passing unit tests with the [C debugging clinic](curriculum/DEBUGGING_CLINIC.md) and [adversarial test matrix](curriculum/EDGE_CASE_MATRIX.md). These show common incorrect approaches, explain why they fail, and provide extra tests to implement independently. The teaching format emphasizes **correctness invariants, object lifetime, error preservation, time/space complexity, and professional code review**.
