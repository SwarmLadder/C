# Deep Dive 04: Array decay, pointer arithmetic and loop invariants

**Outcome:** Write pointer-based algorithms with correct bounds for empty, singleton and large arrays. **Time:** 100–130 minutes.

## An array is not a pointer

An object declared int a[4] is an array of four integers. Most expressions convert its value to a pointer to its first element; exceptions include sizeof and taking the address of the entire array. A parameter spelled int a[4] is adjusted to a pointer parameter. A function cannot discover the length of an array passed as a pointer.

Every algorithm operating on a pointer to contiguous elements should therefore receive an explicit element count, and its contract must say whether NULL is allowed when count is zero. A one-past-the-end pointer may be constructed and compared appropriately but not dereferenced.

## Work through a reversal

~~~c
#include <stddef.h>

void reverse_values(int *values, size_t count) {
    size_t left = 0, right = count;
    while (left < right) {
        --right;
        if (left >= right) break;
        int tmp = values[left];
        values[left] = values[right];
        values[right] = tmp;
        ++left;
    }
}
~~~

The range [left,right) is the unprocessed region. The elements outside it are already in their final reversed positions. The boundaries move toward the center, so the loop terminates. For count=0, it performs zero accesses without computing count-1. Time is O(n), auxiliary space O(1).

Explain the invariant before using it: everything before left and after right is correct; the next swap fixes the pair of outermost remaining elements. This is much stronger than saying "two pointers."

## Pointer arithmetic and aliasing

Pointer subtraction is meaningful for positions in the same array object, producing ptrdiff_t. Arbitrary arithmetic outside an allocated object is not legal just because no dereference occurs yet. Two different pointers can alias storage; if ranges overlap, memcpy has a violated precondition whereas memmove is designed for overlap.

The const keyword modifies what an expression can change, not necessarily every alias to the same object. const int *p prevents mutating an int through p; int *const p prevents changing the pointer variable.

## Practice and adversarial cases

1. Trace the reversal on lengths 0, 1, 2, 5 and 6 with concrete index values.
2. Implement lower_bound for a sorted array using a half-open search interval; prove each update shrinks it.
3. Explain why sizeof(a)/sizeof(a[0]) works for a real local array but not a pointer parameter.
4. Move overlapping bytes from left to right using memmove and explain why memcpy is unsuitable.
5. Prove that a pointer-plus-count function never dereferences NULL when count=0.

**Interview check:** What does one-past-the-end mean? It is a legal sentinel pointer in a valid array context, but dereferencing it has undefined behavior.

**Exit criterion:** You can annotate every index with its legal range and prove the range is maintained.