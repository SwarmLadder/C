# Deep Dive 04: Sorting, binary search and function pointer comparators

**Outcome:** Choose sorting/search algorithms based on complexity, stability and contract requirements. **Time:** 110–140 minutes.

## Big-O is only part of the decision

Insertion sort is O(n²) in worst and average cases but O(n) on already sorted input. It is simple and can be effective for small arrays. Mergesort generally guarantees O(n log n) but often requires O(n) auxiliary storage. Quicksort typically runs in O(n log n) average time but may have quadratic worst cases unless carefully implemented. C's qsort is specified to sort according to a comparator, but no specific sorting algorithm, stability or complexity bound is guaranteed by the standard.

When a question demands stable order among equal keys, do not assume qsort stability. Preserve original indexes as secondary keys or implement a stable sort.

## A correct comparator

~~~c
#include <stdlib.h>

static int compare_ints(const void *left, const void *right) {
    const int a = *(const int *)left;
    const int b = *(const int *)right;
    return (a > b) - (a < b);
}

void sort_values(int *values, size_t count) {
    qsort(values, count, sizeof values[0], compare_ints);
}
~~~

Returning a-b is dangerous: subtraction can overflow when a=INT_MAX and b=INT_MIN, violating the intended ordering. A comparator must be consistent: if a<b and b<c, it must not claim c<a. Sorting results can become meaningless with an inconsistent comparator.

## Binary search invariant

For sorted ascending input, lower_bound returns the first index i where a[i]>=target, or n if none. Maintain [lo,hi) as the search range with 0<=lo<=hi<=n. At midpoint, if a[mid]<target, discard all positions through mid, setting lo=mid+1. Otherwise hi=mid. Since mid is inside [lo,hi), the interval strictly shrinks.

~~~c
#include <stddef.h>
size_t lower_bound_int(const int *a, size_t n, int target) {
    size_t lo = 0, hi = n;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        if (a[mid] < target) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}
~~~

The midpoint formula avoids overflow of lo+hi. Time O(log n), auxiliary space O(1). For duplicates, it returns the first valid position; this tie-breaking property comes from moving hi on equality.

## Practice

1. Explain why comparator subtraction is unsafe at INT_MIN and INT_MAX.
2. Test lower_bound on empty, singleton, all-equal and absent-target arrays.
3. Prove lo<=hi<=n is preserved, and that the search interval shrinks.
4. Explain why sorting and then searching once may be slower than linear search on small input.
5. Design a stable sort for records using original input indexes as tie-breakers.

**Interview check:** Does qsort guarantee O(n log n) or stable ties? No: ISO C specifies behavior in terms of comparison, not a stable algorithm or bound.

**Exit criterion:** You can justify comparator consistency and every binary-search boundary update.