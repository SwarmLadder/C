# Capstone 03 — Dependency-aware job runner simulator

**Estimated duration:** 12–18 hours. **Target:** a deterministic job scheduler with dependencies, bounded queues and clear error semantics. **Related labs:** topology_sort and text_buffer; **related deep dive:** C11 threads and synchronization.

## Scope

Simulate jobs with IDs, durations in ticks, and directed prerequisite edges. The default implementation is single-threaded and portable ISO C17, not a real task execution framework. It should first validate all dependencies and reject invalid IDs or cycles. A ready queue contains jobs whose prerequisite counts are zero. Each tick may launch at most K jobs. Completed jobs unlock dependents; choose the smallest eligible ID to break ties.

The command-line tool accepts a documented text format. It prints a deterministic event trace (start, finish, release) and a summary with total simulated time. Error input must not silently produce a partial schedule. The model is independent of wall-clock time, which makes tests reproducible.

## Representation and correctness

Use a graph adjacency representation and indegree array. A queue may be a fixed-capacity ring, or a dynamic array plus a head index; document why. Maintain the invariants that each node is waiting, ready, running, or done; a node changes state only through valid transitions; each prerequisite edge is satisfied before launching the dependent.

Decide whether a job with zero duration is allowed and how it completes; otherwise reject it. Document whether K=0 is invalid or means no progress. Prevent unsigned-time overflow before adding durations.

## Acceptance tests

1. Empty job set with a documented zero-time result.
2. One independent job; verify its start and finish.
3. Two independent jobs with K=1 versus K=2; compare total time.
4. A diamond dependency graph; dependent starts only after both parents finish.
5. A directed cycle and self-loop; both must be rejected before scheduling.
6. Duplicate edges, unknown IDs and negative or unrepresentable duration in text input.
7. Two simultaneously ready jobs; smallest ID wins.
8. Queue capacity exactly filled and one additional ready job; ensure no overwrite.
9. A large acyclic graph generated with a fixed random seed, checked against a simple reference scheduler.
10. Fault injection on allocation; verify clean shutdown and no published partial graph.

## Optional platform-specific extension

Add a real worker-pool implementation using pthreads or a supported C11 threads implementation. This is **not required** for the portable base course. To do it safely, document mutex-protected state, producer/consumer signaling, worker lifecycle, shutdown synchronization and freeing shared memory only after all threads join. Merely marking counters volatile does not make the implementation correct.

## Review questions

Why does topological ordering prove dependencies can be satisfied? What invariant prevents a job from running twice? How does a queue distinguish full and empty? How is deterministic scheduling useful for tests and incident reproduction?

**Review gate:** Demonstrate a cycle rejected before any job runs, an exact trace for the diamond graph and a documented state-machine invariant.