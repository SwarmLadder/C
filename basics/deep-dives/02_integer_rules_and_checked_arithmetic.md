# Deep Dive 02: Integer promotion, overflow and conversions

**Outcome:** Detect dangerous arithmetic *before* it happens and correctly distinguish signed from unsigned rules. **Time:** 90–120 minutes.

## Model the types, not the machine

ISO C guarantees minimum ranges for fundamental integer types, not a universal 32-bit int or 64-bit long. The exact-width types in stdint.h exist when the implementation supports them. The type size_t represents object sizes; it is not interchangeable with int. Always inspect the operation's actual converted types, not merely its operands' names.

Signed overflow has **undefined behavior**: the compiler is permitted to reason as though a strictly conforming program never does it. Unsigned arithmetic is defined modulo 2 to the width of that unsigned type. This makes an overflow check that evaluates a+b *first* incorrect for signed integers.

## A checked addition contract

~~~c
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>

bool checked_add(int a, int b, int *out) {
    if (out == NULL) return false;
    if (b > 0 && a > INT_MAX - b) return false;
    if (b < 0 && a < INT_MIN - b) return false;
    *out = a + b;
    return true;
}
~~~

Notice the function leaves the output untouched on failure. The bounds expressions themselves are safe: INT_MAX minus positive b is representable, and INT_MIN minus negative b is representable. Test INT_MAX+1, INT_MIN-1, 0+0, and a valid mixed-sign sum.

## Promotions and surprising comparisons

Integer promotions may turn small integer types into int for arithmetic. The expression -1 < 1u is usually false: under common implementations, -1 converts to an unsigned value larger than one. Avoid mixing signed array indexes with size_t lengths. Check that an index is nonnegative before converting it to size_t.

For memory allocation, n*sizeof(T) is also arithmetic. Verify n <= SIZE_MAX / sizeof(T) before multiplication. If n*sizeof(T) wraps, allocation may succeed with insufficient space, and later writes overrun that allocation.

## An important correctness proof

Consider a batch of positive invoice charges stored in int. Maintaining a sum requires induction: before every addition the running total is representable; the guard proves the next sum is representable; therefore the invariant holds after every iteration. If any guard fails, return an error without publishing a partial update. Staging the result locally provides this transaction-like behavior.

## Common traps and practice

Never use if (a+b<a) to detect signed overflow. Do not write a descending size_t loop with i>=0; an unsigned index never becomes negative. Do not assume shifting a signed negative value is portable. Avoid converting a larger integer type into a smaller one without checking range.

1. Implement checked subtraction and checked multiplication for int.
2. Explain the special case INT_MIN multiplied by -1.
3. Allocate n objects safely while checking both multiplication and size-zero behavior.
4. Find the bug in for(size_t i=n-1; i>=0; --i) for n=0.
5. Compare -1 with 1u and explain the usual arithmetic conversions.

**Interview check:** Why is unsigned wrap defined but signed wrap not a safe assumption? Because ISO C specifies different contracts; signed overflow is undefined.

**Exit criterion:** You can justify type conversions and representability for every arithmetic operation in a memory-allocation path.