# C debugging clinic: eight investigations with real failure mechanisms

Use these as code-review exercises, not code to execute unmodified. Each snippet is intentionally wrong. Before reading the diagnosis, identify its precondition, the first operation that violates the contract, a counterexample, and a repair with an invariant. Write an original regression test after every case.

## 1. An off-by-one reversal corrupts even-length data

~~~c
void wrong_reverse(int *a, size_t n) {
    for (size_t i = 0; i <= n / 2; ++i) {
        int tmp = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = tmp;
    }
}
~~~

**Symptom:** Passing n=0 forms an invalid index using unsigned wraparound of n-1, and passing n=2 performs the first swap and then undoes it. A one-element array might appear to work, which masks the bug.

**Root cause:** The loop executes once too often and treats an empty range as though it has two endpoints. **Repair:** Iterate while i < n/2, and never evaluate n-1-i unless n is known nonzero. For positive n the pointer must address at least n valid elements; n=0 may accept NULL.

**Proof prompt:** After k iterations, the first and last k values occupy their final reversed positions, and the unprocessed middle is the only region remaining. Why is a valid-looking output on a singleton insufficient as a test? Add tests for lengths 0,1,2,3 and 4 and apply the algorithm twice.

## 2. realloc loses the last pointer to live memory

~~~c
a->data = realloc(a->data, requested * sizeof *a->data);
if (!a->data) return false;
a->capacity = requested;
~~~

**Symptom:** Memory leaks when allocation fails; the array also risks an undersized allocation if size multiplication wraps.

**Root cause:** Direct assignment overwrites the only owner of the original allocation. On failure realloc returns NULL while the original allocation remains live. **Repair:** First verify requested <= SIZE_MAX / sizeof *a->data, then use a temporary pointer; publish it and the new capacity only after successful allocation.

**Proof prompt:** A failed reserve must preserve original pointer, capacity, length, and elements. What happens to old element aliases after a *successful* realloc? They become invalid, even when the address appears unchanged.

## 3. A signed-overflow check runs too late

~~~c
int result = a + b;
if (result < a) return false;
*out = result;
~~~

**Symptom:** An integer counter changes behavior under -O0 versus -O2 near INT_MAX.

**Root cause:** Evaluating an overflowing signed sum already invokes undefined behavior. A comparison afterward cannot recover defined semantics, and negative b makes the comparison inappropriate anyway. **Repair:** For positive b check a <= INT_MAX-b; for negative b check a >= INT_MIN-b; only then calculate a+b.

**Test:** INT_MAX+1 and INT_MIN-1 fail without modifying output. INT_MIN+INT_MAX succeeds and yields -1. Explain why unsigned wrap, though defined, is not necessarily acceptable when values become allocation lengths.

## 4. Binary input mistakenly treated as a C string

~~~c
size_t length = strlen((const char *)payload);
~~~

**Symptom:** A three-byte payload containing {65,0,66} is reported as length one.

**Root cause:** strlen stops at the first zero and assumes a terminated accessible string. For an arbitrary binary buffer with no terminator, even calling strlen violates the input contract. **Repair:** Retain a pointer-plus-length pair from the file or network read, and check offset <= size and field_length <= size-offset before any access.

**Test:** Empty bytes, embedded zeros, high-bit bytes, and a buffer with no zero. Do not run the broken version on a nonterminated buffer merely to observe undefined behavior.

## 5. Sorting with subtraction can overflow

~~~c
int comparator_bad(const void *x, const void *y) {
    return *(const int *)x - *(const int *)y;
}
~~~

**Symptom:** A sort returns inconsistent order for extreme negative and positive values.

**Root cause:** INT_MIN-INT_MAX is not representable as int, so the comparator invokes undefined behavior. It can also violate transitivity. **Repair:**

~~~c
int comparator_good(const void *x, const void *y) {
    const int a = *(const int *)x;
    const int b = *(const int *)y;
    return (a > b) - (a < b);
}
~~~

**Test:** INT_MIN, INT_MAX, zero, negatives, duplicates, and record keys with stable-tie requirements. ISO C qsort does not promise stable sorting.

## 6. The parser publishes partial output before validation

~~~c
/* Invalid read and mutation if the input is short or malformed */
out->kind = read_kind(bytes);
if (length < 9 || bytes[2] != 1) return false;
~~~

**Symptom:** After receiving malformed input, the caller's previous FrameHeader has changed.

**Root cause:** Output mutation and byte access occur before validation. **Repair:** Check pointers and lengths, decode all fields into a local temporary struct, validate magic/version/limit, then assign the complete output only on success. This enforces the strong failure guarantee.

**Test:** Initialize output to distinctive sentinels, supply every truncated length 0 through 8, bad version, bad magic and oversized payloads; prove the sentinels remain.

## 7. A FIFO queue does not actually wrap

~~~c
q->head += 1;
q->size -= 1;
~~~

**Symptom:** A bounded queue eventually indexes past the buffer, or returns data out of order after several rotations.

**Root cause:** Head grows linearly but the physical array is a ring. **Repair:** For nonzero capacity, advance head modulo capacity, and maintain 0 <= size <= capacity, head < capacity. For a general dynamic capacity, prevent addition overflow as well.

**Test:** Fill eight elements, pop three, push three, then pop eight. Assert the exact FIFO sequence rather than checking only final size.

## 8. volatile is mistaken for thread synchronization

~~~c
volatile unsigned counter = 0;
/* Two threads concurrently execute: */
counter++;
~~~

**Symptom:** Two threads each perform 1000 increments, but the expected final value cannot be relied upon.

**Root cause:** volatile does not make a read-modify-write operation atomic or establish a happens-before relationship. Conflicting unsynchronized accesses are a data race and cause undefined behavior in C's memory model. **Repair:** For an isolated count use atomic_uint with atomic_fetch_add; for several related queue fields, use a mutex or a carefully proven atomic protocol.

**Test:** Trace how two threads can both read 5 and both write 6; explain why the race is worse than one lost increment. State which C11/platform features your example requires; not all ISO C17 targets support the same threading libraries.

---

## Repeatable review method

1. **Find the contract:** caller preconditions, required object size, output on failure, and ownership.
2. **Locate first dangerous operation:** integer arithmetic, pointer formation, dereference, mutation, allocation, I/O or free.
3. **Check validation order:** all bounds and arithmetic checks must precede the unsafe operation they guard.
4. **Trace hostile cases:** zero length, single element, duplicate key, extreme integer, malformed stream, failed allocation.
5. **Prove a preserved invariant:** what remains true before and after every iteration or state transition.
6. **Inspect every early return:** which objects remain allocated and which caller-visible values have changed?
7. **Create an independent regression test:** compare against a simple oracle when useful.
8. **Explain tooling limits:** compiler warnings, sanitizer runs and fuzzing are evidence, not formal proofs.

Pair each investigation with a real [mastery lab](../mastery/README.md) and [edge-case matrix](EDGE_CASE_MATRIX.md). A strong learner explains why the mistake is invalid before executing the code.
