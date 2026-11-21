# Deep Dive 02 — C11 threads, atomics and data races

**Outcome:** Describe correct synchronization and avoid false thread-safety claims. **Time:** 150 minutes.

## A race is not just a lost update

Two threads access the same non-atomic object without the required synchronization, at least one writes, and a data race occurs. In C's memory model, that is **undefined behavior**. Even when a demonstration sometimes reports 6 instead of 7, the issue is more serious than the lost increment.

Declaring an ordinary shared variable volatile does not make increments atomic and does not create a happens-before relationship.

## Atomic counters

~~~c
#include <stdatomic.h>

static atomic_uint completed;

void record_job(void) {
    atomic_fetch_add_explicit(&completed, 1U, memory_order_relaxed);
}
~~~

This is appropriate if only the counter's numeric value needs to be atomic. Relaxed ordering does not publish unrelated data. For a producer to initialize a message and publish a ready flag, release/acquire synchronization (or a mutex) may be required. The protocol must also prevent the producer from overwriting the message before the consumer finishes reading it.

## Protected invariants

A queue has more than one field: head, length, capacity and buffer. The condition 0<=len<=cap spans them. A mutex can protect the entire transition, whereas making one field atomic does not magically make all other fields consistent. Good concurrency design states which lock protects which fields, how locks are ordered to avoid deadlock, and who owns memory during shutdown.

C11 threads.h support is an optional implementation facility. Some platforms require specific toolchains, libraries or POSIX threads. This chapter teaches standard memory semantics; do not assume the example with multiple threads is universally buildable on every C17 target.

## Guided timeline

Producer: write payload bytes; release-store ready=true. Consumer: acquire-load ready until true; then read payload. This orders initialization before consumption, but does **not** by itself support repeated messages or safely reclaim the payload. Define a separate acknowledgement or use a queue with properly protected ownership.

## Exercises

1. Explain why volatile int total is not a thread-safe counter.
2. Draw the two-thread interleaving that loses an increment.
3. Compare mutex protection with atomic fetch_add for a standalone count.
4. Describe a memory-order bug in a producer/consumer handoff using only relaxed operations.
5. Design a shutdown protocol preventing a consumer from reading freed queue storage.

**Interview checkpoint:** Does atomic imply all data in a struct is protected? No, it applies to the atomic objects and specified ordering effects.

**Exit criterion:** Every conflicting shared access has a synchronization story and a lifetime contract.