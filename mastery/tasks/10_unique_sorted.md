# Mastery I4 — Stable in-place deduplication with input validation

**Level:** Intermediate · **Time:** 90–120 minutes · **Implementation:** \`mastery/starter/unique_sorted.c\`

## Problem and failure guarantee

Implement \`bool unique_sorted_i32(int32_t *values, size_t n, size_t *out_count)\`. Given a nondecreasing sequence, retain **one copy of each distinct value** at the start of the same array, in original order, and store the number retained in \`*out_count\`. It is not necessary to scrub the unused tail. Empty input succeeds, permits values=NULL, and reports zero. An output pointer is required.

Unlike a typical interview version, this API must **reject unsorted input**. Crucially, rejection must leave both the array and \`*out_count\` unchanged. This makes the exercise more realistic: some callers cannot tolerate discovering an invalid input after partial mutation.

## The two-phase solution

**Phase 1: validate without mutation.** Scan adjacent pairs; if any \`values[i] < values[i-1]\`, reject. The scan is O(n) and ensures every later comparison can rely on sorted order.

**Phase 2: compact with two indexes.** Keep a write count and scan all n input values. Copy the current value to \`values[write]\` only if it differs from the last retained value (or if write is zero), then increment write. Because write never exceeds read+1, writes never destroy unprocessed input.

Trace \`[-4,-4,-1,0,0,0,5,5]\`: after consuming both -4 values, prefix \`[-4]\` and write=1; after -1, prefix \`[-4,-1]\`; after three zeros, prefix \`[-4,-1,0]\`; after two fives, prefix \`[-4,-1,0,5]\`. Report 4. Input \`[0,5,3,9]\` must fail during validation, leaving all four elements and the original out_count untouched.

## Proof and complexity

**Loop invariant:** before processing read, the first write elements are the sorted sequence of distinct values among the already processed positions. Appending exactly when the value differs from the last retained one preserves both uniqueness and relative order. Sortedness is what makes adjacent comparison sufficient; a general unsorted deduplicator would need a hash set or O(n²) scanning.

Total time O(n), auxiliary space O(1). The function mutates the caller's buffer **only on success**. On failure no partial write occurs because validation precedes compaction.

## Tests and extensions

Test n=0, n=1, all-equal, all-distinct, negatives, INT32_MIN/INT32_MAX, one inversion late in the array, and NULL pointers. Run \`make mastery-check TASK=unique_sorted\`. Extend to a struct array with a key extractor and consider what stability means for associated payloads. Compare to \`qsort\` followed by dedup: sorting may reorder unrelated fields and costs O(n log n).

**Interview checkpoint:** Why does the order of validation versus mutation matter for a strong failure guarantee?

**Review gate:** Explain how every value remains readable until processed and why unsorted input does not modify state.