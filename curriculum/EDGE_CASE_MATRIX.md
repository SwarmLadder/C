# Adversarial testing matrix for twelve C17 mastery labs

A passing reference suite checks expected behavior on selected fixtures. This matrix is a source of **independent** tests, not a substitute for code review. Test the return value *and* the state of outputs. Avoid using a copy of the implementation as the test oracle.

| Lab | Adversarial input | Property or guarantee | New variation |
| --- | --- | --- | --- |
| checked_add | INT32_MIN, INT32_MAX, -1, 0, 1 | Addition is never executed when mathematically unrepresentable; failure preserves output | Checked subtraction without negating INT32_MIN |
| parse_decimal | empty, 000, UINT32_MAX, max+1, trailing letter | Accepted prefixes remain representable; no partial result | Length-delimited decimal parser |
| reverse_span | n=0,1,2, odd/even, 0x00 and 0xff bytes | No out-of-range access; reverse(reverse(x)) equals x | In-place rotation |
| parse_hex | mixed case, eight F digits, nine zeros, 0x prefix, signs | Exactly one to eight valid digits; output retained after error | Strict 64-bit parser |
| text_buffer | zero append, capacity boundary, SIZE_MAX, simulated realloc failure | NUL at length, length<capacity, no ownership loss | Appending overlapping source with temporary storage |
| byte_histogram | empty file, zeros, 0xff, large file, read error | Published counters reflect only complete successful reads | Most-common-byte tie-breaking |
| lower_bound | empty, all equal, duplicates, absent key, extremes | Half-open interval shrinks, earliest qualifying index | upper_bound and equal_range |
| unique_sorted | all equal, negatives, late inversion, empty | Reject unsorted input before mutation | Deduplicate stable records by key |
| frame_header | truncations 0-8, bad magic/version, max+1 length | No byte read before validating size; output unchanged on failure | Encoder/decoder roundtrip |
| topological | duplicate edges, cycle, self-loop, zero vertices | Every selected vertex has zero current indegree | Heap-based deterministic scheduler |
| ring_queue | full, empty, wraparound, reset, UINT32_MAX | FIFO order and correct head/size bounds | Runtime-sized ring with overflow checks |
| dag_distances | unreachable node, alternative route, huge weights, cycle | Graph validated before output; best reachable distance | Cross-check with Dijkstra on small DAGs |

## Three test strategies that reveal deeper errors

**Independent oracle:** For lower_bound, compare against an obvious linear scan over small sorted arrays. For ring_queue, compare against a slow reference queue that shifts an array on every pop. For a DAG with at most eight nodes, enumerate paths in a deliberately simple reference implementation and compare shortest distances. Use a fixed random seed to make failing cases reproducible.

**Failure preservation:** Initialize output to sentinels before invalid calls. On a bad frame, ensure all fields stay identical. On an unsorted deduplication input, ensure the entire input array and count stay the same. A test that asserts only false can miss corruption and half-published state.

**Metamorphic tests:** Reversing twice restores a byte span; adding a duplicate edge to a DAG does not change shortest distances; inserting then removing one queue element returns that value; parsing uppercase and lowercase hex equivalents yields the same integer; running unique_sorted twice does not change its retained prefix.

## Reproducible tooling

Use both supported compilers when possible:

~~~sh
make clean
make mastery-reference CC=gcc CFLAGS="-O1 -g -fsanitize=undefined"
make clean
make mastery-reference CC=clang CFLAGS="-O1 -g -fsanitize=undefined"
~~~

On a supported local system, use AddressSanitizer to detect many out-of-bounds and lifetime mistakes. Build a separate diagnostic binary rather than claiming an optimized production build is also instrumented. A clean sanitizer run never proves that all executions are memory-safe.

## Evidence template

For each lab, record the preconditions; postconditions; ownership; error semantics; invariant or induction proof; worst-case time and auxiliary space; at least three original tests with exact expected results; one diagnostic build; and a one-paragraph bug postmortem. This is more useful than a raw test count and supports technical interviews and professional code review.

**Warning:** Deliberately malformed input is fine. Running intentionally unsafe third-party programs requires an appropriate isolated environment; do not run malicious executables on your own machine.
