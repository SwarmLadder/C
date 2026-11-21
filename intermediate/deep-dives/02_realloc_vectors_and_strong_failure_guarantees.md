# Deep Dive 02: Resizable vectors, capacity growth and realloc

**Outcome:** Implement a dynamic array that preserves its contents under allocation failure. **Time:** 120–150 minutes.

## Define the invariant first

For a vector of ints with fields data, len and cap: 0 <= len <= cap; when cap>0, data points to storage for at least cap ints; the unique owner of data is the vector. When cap==0, data may be NULL. Every mutating method must preserve these invariants both on success and failure.

The common mistake is assigning the realloc result directly to data. If realloc fails, the original allocation remains valid but the original pointer is lost. Always use a temporary variable. Before doubling capacity, check capacity <= SIZE_MAX/2 and before multiplying by element size, check new_capacity <= SIZE_MAX/sizeof(int).

## Worked reserve routine

~~~c
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t len;
    size_t cap;
} IntVector;

int vector_reserve(IntVector *v, size_t requested) {
    if (!v || v->len > v->cap) return 0;
    if (requested <= v->cap) return 1;
    if (requested > SIZE_MAX / sizeof *v->data) return 0;
    int *new_data = realloc(v->data, requested * sizeof *v->data);
    if (!new_data) return 0;
    v->data = new_data;
    v->cap = requested;
    return 1;
}
~~~

This reserves capacity without changing len and retains existing values if realloc fails. The caller still owns v even if the request fails. The first call may use a zero-initialized vector. Note that requests of zero or unchanged capacity should not trigger realloc; the behavior of realloc(ptr,0) is avoided.

## Amortized analysis

If the vector grows geometrically from 1 to 2,4,8,..., each append may occasionally copy all existing elements, but across n appends the total copying is bounded by a geometric series smaller than 2n. Therefore appending is amortized O(1) per element while an individual growth step remains O(n). Increments by one capacity every time instead cause O(n²) total copying.

## Ownership and iterators

After a successful reserve that grows storage, all old pointers into the buffer must be treated as invalid, even if the allocator returns the same numerical address. Do not retain pointers to vector elements across possible growth. Internal indices remain meaningful if the vector retains order.

## Failure injection and tests

An advanced test can substitute a failing allocator via a dependency wrapper. Request capacity beyond representable memory first to exercise deterministic rejection; inspect that data, len and cap did not change. Test append on an empty vector, growth at the boundary, clearing without release and release twice only if your API explicitly makes repeat release safe.

## Practice

1. Add vector_push with geometric capacity growth and failure preservation.
2. Add vector_pop that returns false without writing when len==0.
3. Write a test that stores an element pointer, triggers growth and then deliberately avoids dereferencing the old pointer.
4. Analyze geometric versus linear growth with a concrete n=16 trace.
5. Explain how a vector can avoid reading uninitialized capacity slots.

**Interview check:** Why does realloc failure not leak when used with a temporary? Because the original pointer and allocation remain owned by the caller.

**Exit criterion:** You can prove len<=cap before and after every operation and survive allocation failure without data loss.