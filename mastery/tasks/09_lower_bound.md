# Mastery I3 — Binary search for the first qualifying index

**Level:** Intermediate · **Time:** 75–110 minutes · **Implementation:** `mastery/starter/lower_bound.c`

## Input and output contract

Write `bool lower_bound_i32(const int32_t *values, size_t n, int32_t key, size_t *out_index)`. The caller guarantees values are sorted in **nondecreasing** order. Find the first index whose value is **greater than or equal to** key. If every value is smaller, return n; do not return a random index or -1. Empty input is valid: n=0 allows values=NULL and must return 0. A NULL output pointer, or NULL values when n>0, is invalid and must leave all output state unchanged.

This lesson intentionally makes "sorted input" a documented precondition rather than spending O(n) to verify it. Compare that tradeoff with the next lab, which explicitly validates sortedness to guarantee failure preservation.

## Worked trace and invariant

For `[-7, -1, -1, 0, 3, 3, INT32_MAX]`, the lower bound for -1 is index 1, for 2 is index 4, and for 3 is also index 4. For a key greater than all present values the result is 7.

Maintain a **half-open interval** `[low, high)`. The answer is guaranteed to lie somewhere in `[low, high]`; indexes strictly before low have been shown to contain values < key, while indexes at or after high have been ruled out as first qualifying candidates. Begin low=0 and high=n. At each iteration use `middle = low + (high-low)/2` to avoid overflow of low+high. If `values[middle] < key`, set low=middle+1; otherwise set high=middle. The interval strictly shrinks until low==high.

Do not use the first matching equality as an excuse to return immediately: duplicates might place an earlier equal value to its left. That is the most common incorrect solution to a "first index" interview variant.

## Complexity and failure modes

Each step removes about half the candidate interval, so the number of iterations is Θ(log(n+1)), space O(1). A linear scan is Θ(n), but can be faster on extremely small inputs; judge algorithm requirements before premature micro-optimization. This function performs no mutation to the source array.

Test: empty, singleton, all equal, negatives, duplicates, absent key, smallest/largest int32 values, and invalid pointers. Run `make mastery-check TASK=lower_bound`.

## Interview and extension

Prove termination with the decreasing potential `high-low`. Implement upper_bound (first index > key) by changing only the comparison. Then use the difference `upper_bound(key)-lower_bound(key)` to count duplicates in O(log n) time without scanning them. Explain why calling a sort first changes the overall complexity and may violate input order requirements.

**Review gate:** You can draw every boundary update, prove no out-of-bounds read, and demonstrate correct behavior with duplicates.