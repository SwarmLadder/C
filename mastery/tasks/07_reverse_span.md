# Mastery B3 — In-place byte-span reversal

**Level:** Foundations · **Time:** 45–75 minutes · **Implementation:** `mastery/starter/reverse_span.c`

## What you are building

A network decoder sometimes needs to reverse a raw byte span for a transformation or test fixture. Write `bool reverse_span(uint8_t *data, size_t length)`. Change the bytes **inside the same buffer**, without allocating another array. Return true for any valid span. When length is zero, accept a NULL pointer and do nothing. If the pointer is NULL with positive length, return false without writing anything.

The caller guarantees a valid writable array containing at least `length` elements when length is positive. This function cannot inspect the allocation behind an arbitrary pointer; do not falsely claim it detects dangling or undersized storage. It must support every byte value, including 0 and 255. Treat input as **binary bytes**, not a C string: there is no NUL-terminator requirement.

## Work through two traces

For `[0, 255, 2, 3, 4]`: first swap positions 0 and 4, giving `[4,255,2,3,0]`. Next swap positions 1 and 3, giving `[4,3,2,255,0]`. The center element stays in place. For `[7,9]`, a single swap gives `[9,7]`. For `[]` and `[7]`, there is no swap.

**Loop invariant:** after k successful iterations, the first k and last k bytes are in their final reversed positions. The unprocessed middle remains available and the two swap indexes are within [0,length). You need at most `length/2` swaps. A safe implementation checks the length before ever computing `length-1-index`, so zero length never wraps to SIZE_MAX and becomes a bogus address.

## Approach and complexity

Use an index from zero to `length/2`, swapping it with `length - 1 - index`. The algorithm performs Θ(n) byte operations, constant auxiliary memory, and **zero heap allocations**. Do not call `strlen`; a byte array may contain embedded zeros.

## Tests you should write first

1. NULL with length 0 succeeds; NULL with length 1 fails.
2. Empty, one-element, and two-element spans.
3. An odd-length span with values 0 and 255.
4. Apply the function twice and check the original bytes return.
5. Compare against a simple independently generated reverse copy for random small spans.

Run `make mastery-check TASK=reverse_span`. The grader tests behavior but cannot verify that an arbitrary caller pointer references valid storage; state that as a precondition.

## Interview and stretch

Explain why a pointer plus length is preferable to a C string for raw network payloads. Extend the exercise with `rotate_span` and distinguish a copying implementation from an in-place three-reversal method. For very large lengths, explain why calculating `length-1` must not occur before checking an empty span.

**Review gate:** demonstrate the loop invariant, exact memory usage and bounds proof without consulting the reference.