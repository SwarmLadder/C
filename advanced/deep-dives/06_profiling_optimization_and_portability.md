# Deep Dive 06 — Performance, profiling and portable C architecture

**Outcome:** Measure meaningful bottlenecks, preserve correctness and document platform boundaries. **Time:** 120 minutes.

## Optimization starts with evidence

Repeated small allocations, O(n²) string concatenation, cache-missing pointer chains and excessive system calls often matter more than a minor arithmetic instruction. First identify the dominant cost with representative workloads and report input sizes, toolchain, build flags, warm-up behavior and variability. Change one major factor at a time. Keep correctness tests identical before and after optimization.

A benchmark that computes a value but never uses it may be optimized away. Make the result observable and validate it against an independent expected value.

## A measured loop with defined arithmetic

~~~c
#include <stddef.h>
#include <stdint.h>

uint64_t checksum(const uint32_t *values, size_t count) {
    uint64_t result = 0;
    for (size_t i = 0; i < count; ++i)
        result += values[i];
    return result;
}
~~~

For a target with uint64_t, the unsigned accumulation has defined modular arithmetic. The caller still must provide a valid array of count elements. Analyze both O(n) work and memory-bandwidth limits; the latter can dominate arithmetic cost for large arrays.

## Profile before micro-optimizing

A sampling profiler associates CPU time with hot functions or instruction ranges, but results depend on sampling, permissions and workload. Use suitable tools for your target, such as perf on supported Linux environments. Inspect assembly when a specific optimization claim requires it. Never rely on undefined behavior merely because one compiler produces faster code.

## Design for portability deliberately

Keep ISO C17 algorithms and parsing in portable translation units; isolate POSIX files, sockets, threads or platform-specific syscalls behind a documented adapter. Data stored on disk or sent across a network needs explicit widths and byte order; serializing raw structs makes layout an accidental ABI contract.

Run GCC and Clang in CI where possible, and test both optimized and diagnostic configurations. Thread libraries, atomics, endian behavior and floating-point details can vary across targets; label guarantees and assumptions honestly.

## Practice

1. Benchmark a vector grown geometrically versus one resized by a single element, for a controlled input size.
2. Find an O(n²) repeated string-concatenation loop and replace it with a single buffered join.
3. Explain how a benchmark's useful work could disappear under optimization.
4. Inventory platform dependencies in a real project and propose an adapter boundary.
5. Produce a performance report with input, timing method, correctness result and measured change.

**Interview checkpoint:** What do you optimize first? The largest measured cost that can be changed without breaking the contract.

**Exit criterion:** You provide reproducible numbers, tests proving unchanged behavior and a clear portability statement.