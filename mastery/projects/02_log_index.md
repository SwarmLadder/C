# Capstone 02 — Log indexing and query engine

**Estimated duration:** 10–16 hours. **Target:** a CLI that reads lines such as timestamp, level, component and message, then performs deterministic queries. **Related concepts:** resizable vectors, strict parsing, hashing, sorting, profiling.

## Input and query contract

Define one explicit grammar for each log record. For example, an ISO-8601 timestamp, one of INFO/WARN/ERROR, an ASCII component token, and the remainder as a bounded message. Decide whether spaces may occur in the message and whether empty messages are allowed. Reject too-long or malformed records with line number and reason. Do not use scanf without width and error checking.

Queries must support: count records per level; list components sorted by frequency with alphabetical tie-breaking; and show the top N most recent error records in stable timestamp order. Define handling of identical timestamps and N=0.

## Proposed representation

Store parsed metadata in a dynamically grown vector. For component counts, design an open-addressed hash map with empty/occupied/deleted slot states or use a sorted array and justify its complexity. Treat allocations as owned resources, use checked growth and avoid retaining element pointers across realloc. If keeping message strings, ensure each allocation's owner and destructor are explicit.

Use qsort only with a comparator that does not subtract potentially large integer fields. If stable ordering is required, store input position as an explicit secondary key.

## Acceptance tests

1. Zero records and blank input with documented behavior.
2. One valid INFO record.
3. Duplicate component names, case-sensitive or case-insensitive according to documented grammar.
4. Equal timestamps with deterministic input-order tie-breaking.
5. N=0, N=1 and N greater than the number of records.
6. An invalid timestamp, unsupported level, missing component, and message exceeding configured limit.
7. A stream containing an embedded NUL byte: reject under your textual grammar rather than silently truncating.
8. A fixture of 100,000 lines generated with a fixed seed; record peak memory and query time.
9. A forced vector reallocation failure with state preservation.
10. Compare hash-count results to an independent simple counting oracle on random small logs.

## Benchmark methodology

Measure parsing and each query separately. State compiler, flags, input size, device, process and repetition count. Compare an O(n²) naive counting implementation with a better representation, but avoid claiming improvement without measured numbers. For large input, CPU cache locality and allocation overhead can dominate even when two designs have similar Big-O bounds.

## Review questions

Can a malformed line partially update the index? Are diagnostics useful? How does the hash table handle tombstones? Which operations are O(n), O(n log n), or expected O(1)? What happens when the last allocation fails?

**Review gate:** Demonstrate deterministic output, no leaks under the tested configuration, correct failure handling and reproducible performance results.