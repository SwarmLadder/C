# C mastery assessment — observable competence, not checklist inflation

A learner has not mastered C merely because 87 small-function checks pass. Review both behavior and the code's reasoning. The categories below total 100 points.

| Category | Points | What a reviewer examines |
| --- | ---: | --- |
| Correctness and regression testing | 30 | Core checks, mastery checks, independent edge cases, failure injection, no untested error paths |
| Memory, arithmetic and lifetime safety | 25 | Bounds proofs, initialization, output preservation, ownership, cleanup, no undefined behavior |
| API and systems design | 20 | Multi-file boundaries, stable error semantics, reproducible build, correct wire/storage representations |
| Reasoning and algorithmic analysis | 15 | Invariants, correctness proofs, complexity, comparisons between approaches |
| Portability, diagnostics and performance | 10 | GCC/Clang builds, sanitizer interpretation, platform boundaries, realistic benchmark evidence |

## Non-negotiable safety gates

Any one of these blocks a passing mastery result until fixed, regardless of the numerical score: reproducible use-after-free or double-free; exploitable out-of-bounds read/write; deliberate signed-overflow reliance; failed resource cleanup in demonstrated paths; unvalidated external lengths used to allocate or index; or a false portability/security claim (such as calling a POSIX syscall ISO C, or claiming sanitizers prove safety).

An unfinished starter that passes only because assertions are disabled is not a valid submission. Do not evaluate third-party untrusted C snippets outside a suitable isolated environment.

## Suggested attainment levels

- **Foundation (at least 60/100, no critical gate):** All basics workshop checks and basics mastery labs, sound array/string contracts and a reproducible build.
- **Independent C developer (at least 80/100, no critical gate):** Full intermediate checks, documented ownership, robust parsing, at least one project with adverse-input tests.
- **Systems-capable C developer (at least 90/100, no critical gate):** All levels and twelve mastery labs; one integrated capstone, a failure-injection demo, a binary/stream format explanation, and a measured performance or complexity argument.

Scores describe **demonstrated work**, not a hiring or certification guarantee. Safety failures always take precedence over an aggregate score.

## Oral review prompts

1. Draw the lifetime and ownership of every allocated block in your project and show how it is freed on each failure path.
2. Demonstrate one length/arithmetic validation that prevents overflow before memory access.
3. Explain the difference between compile error, linker error, runtime error and undefined behavior.
4. Explain why an input byte buffer is not automatically a null-terminated C string.
5. Show how a partial read/write or malformed record is handled without publishing inconsistent state.
6. Explain why raw struct serialization does not provide a portable wire protocol.
7. Trace a queue or hash-table invariant through insertion, deletion and failure.
8. Defend the largest measured bottleneck and the change made to address it.

## Evidence template

For each major function, record: preconditions; postconditions; failure behavior; ownership; complexity; test identifiers; sanitizer build command; one deliberate edge case; and any platform-specific assumption. For each capstone, include a README with repeatable build commands and a minimal malformed-input fixture.

## Mock reviews

**Mock A (45 min):** 10 minutes C type/promotions, 15 minutes array/string parser, 10 minutes boundary tests, 10 minutes explain ownership.

**Mock B (60 min):** 15 minutes dynamic storage design, 20 minutes implement and debug a safe append, 10 minutes error-path walkthrough, 15 minutes tests/complexity.

**Mock C (75 min):** 15 minutes binary protocol design, 30 minutes multi-file parser implementation, 15 minutes fuzz/truncation reasoning, 15 minutes portability and performance review.

In each mock, speak your invariant before typing and evaluate the result against the same score categories above.

## Evidence required for the enriched mastery track

For each of the **twelve** labs, retain a failed-input test, a normal-input test, a boundary test, and a short proof of the key invariant. Review the [edge-case matrix](EDGE_CASE_MATRIX.md) but write your own tests rather than copying the existing grader. Completing all twelve labs is **necessary but not sufficient** for the highest attainment level: a reviewed multi-file capstone and failure-path inspection remain required.
