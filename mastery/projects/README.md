# C systems-engineering capstones

The nine original projects practice core workshop APIs. These three larger capstones demand **multi-file implementation**, failure-path discipline, documented ownership and an engineering review. They are intentionally *not* auto-graded by the small function-level test harness; each specification includes acceptance tests that you must implement and demonstrate.

| Capstone | Main techniques | Deliverable |
| --- | --- | --- |
| [Telemetry stream decoder](01_telemetry_decoder.md) | Binary protocols, streams, bounded allocation, checksums | Reliable CLI that rejects malformed frames |
| [Log index and query engine](02_log_index.md) | Dynamic arrays, hash tables, comparators, deterministic output | CLI with indexed queries and benchmarks |
| [Dependency job runner](03_dependency_runner.md) | Graph algorithms, queues, state machines, rollback | Deterministic simulated scheduler |

## Required engineering artifacts

Every capstone submission needs a README stating scope, build commands, portability assumptions and exact input grammar; source split into interface headers and .c implementation files; automated unit and integration tests; a test matrix for empty/truncated/invalid data; diagnostic builds with sanitizers; a documented ownership table; and a performance or complexity report for the primary algorithm.

### Review sequence

1. Produce a valid minimum example and one invalid example before implementation.
2. Design data types and invariant ownership first, then parser/state transitions.
3. Build the smallest vertical slice and test its error paths.
4. Add deterministic fixtures and adversarial cases.
5. Run at least two compilers, note any platform-dependent requirements.
6. Present a failure-injection demonstration with state unchanged where promised.

Use the [assessment rubric](../../curriculum/ASSESSMENT.md). A passing demo is not sufficient without readable contracts, comprehensive failure checks and safe cleanup.

**Safety:** Test only with files you control; programs that parse malicious files should run in a suitable isolated environment. None of these specifications asks for privileged operations or network exploitation.