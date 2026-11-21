# Twelve-week C mastery roadmap

**Audience:** someone comfortable with programming basics who wants reliable C17 systems skills. **Typical commitment:** 7–10 focused hours per week. These are milestones, not calendar deadlines: advance only after passing the week's exit criteria. A newcomer can spend more time on weeks 1–4.

## Weekly learning loop

Reserve two sessions for reading and tracing, two for implementing and testing, one for debugging or a variation, and one for reviewing mistakes. A useful session ends with a checked C file, a boundary-case test, and a written explanation of one invariant. Avoid copying reference solutions before attempting the starter.

| Week | Read and understand | Implement and demonstrate | Exit gate |
| --- | --- | --- | --- |
| 1 | Basics Clocks/branches; deep dives 01–02 (builds, overflow) | First 8 core functions; mastery checked_add | GCC and Clang strict builds; no signed-overflow reliance |
| 2 | Basics loops/arrays; deep dive 04 | Array search, reversal, windows; original workshops | Prove indexes remain in bounds for empty and 1-element cases |
| 3 | Basics strings/structs; deep dives 03 and 05 | Remaining basics functions; strict decimal parser | Explain the lifetime and owner of every pointer |
| 4 | Deep dive 06 (debugging), three basics projects | Basics review and boundary regression suite | All basics checks plus both mastery labs; reproduce and fix one injected bug |
| 5 | Intermediate outputs/buffers; deep dives 01–02 | Output contracts, dynamic vector and text buffer | Buffer remains unchanged on allocation failure |
| 6 | Intermediate parsing/streams; deep dive 03 | Strict parser, stream histogram, malformed records | Distinguish invalid text, I/O failure and normal EOF |
| 7 | Intermediate sorting/callbacks; deep dives 04 and 06 | Binary search, comparators, callbacks, macro review | Comparator consistency and binary-search invariant explained |
| 8 | Intermediate projects; deep dive 05 (wire format) | All intermediate functions; start telemetry capstone | Demonstrate endian-safe decoding and record truncation rejection |
| 9 | Advanced allocation/lists; deep dive 01 (UB) | Ownership and linked-structure exercises; sanitizer reports | No use-after-free, double-free or invalid arithmetic in inspected code |
| 10 | Advanced rings/bits; deep dive 04 | Queues and hash-table design; topological lab | Explain collision/tombstone and queue capacity invariants |
| 11 | Advanced binary/protocols; deep dives 02, 03 and 05 | Frame decoder; POSIX error-loop analysis; concurrency proof | Clearly separate ISO C from C11/POSIX; reject malformed frames |
| 12 | Deep dive 06; advanced projects and capstone | Final integration project, benchmarking, mock interviews | 100-point assessment with no critical safety failures |

## Daily concrete sequence

1. Read one section and paraphrase it in your own words without opening the source.
2. Trace a normal case and a hostile edge case on paper.
3. Write a function contract: valid pointer ranges, input grammar, ownership, output on failure.
4. Implement a solution in the corresponding starter.
5. Compile with -std=c17 -Wall -Wextra -Werror -pedantic. Test focused cases.
6. Run an appropriate sanitizer on a supported local toolchain, then debug at least one failure path.
7. Derive complexity and explain why the chosen data representation is appropriate.
8. Solve a variation or independently reimplement after 7 days.

## Spaced repetition schedule

After solving a problem, revisit it the next day, three days later, one week later and roughly four weeks later. First review only your notes; then implement a fresh version with no reference code visible. Record errors by category: bounds, integer promotion, lifetime, API contracts, I/O, algorithmic invariant and portability. A repeated failure category becomes the next practice priority.

## What the scores mean

The existing 81 workshop/project checks and six mastery labs are automated **behavioral** evidence, not proof of C expertise. You also need independent tests, reviews of error paths, a multi-file capstone, and clear oral explanations. Use [the assessment rubric](ASSESSMENT.md). Passing the provided tests with undefined behavior or memory leaks does not count as proficiency.

## Target deliverable after week 12

A working, tested C17 project with documented interfaces, a predictable build, a finite test suite including hostile inputs, a failure/ownership map, a compiler/sanitizer run, and a profile or complexity report. A reviewer should be able to clone, build and reproduce your result without personal instructions.

**Recommended capstones:** [Telemetry frame decoder](../mastery/projects/01_telemetry_decoder.md), [Log index](../mastery/projects/02_log_index.md), or [Dependency scheduler](../mastery/projects/03_dependency_runner.md). Finish one deeply before starting another.
