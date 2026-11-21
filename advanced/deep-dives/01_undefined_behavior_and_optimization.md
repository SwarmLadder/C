# Deep Dive 01 — Undefined behavior, sequencing and optimization

**Outcome:** Recognize undefined operations before they happen and distinguish language guarantees from observed outputs. **Time:** 120 minutes.

## Mental model

C describes an abstract machine. Defined behavior follows the standard's rules; implementation-defined behavior is a choice that must be documented; unspecified behavior permits multiple conforming outcomes; **undefined behavior (UB)** places no requirements on execution. Examples include signed overflow, dereferencing an invalid pointer, out-of-bounds access, some unsequenced modifications, and accessing memory after its lifetime ends.

A program may appear correct at -O0 and fail at -O2. The optimizer can assume well-defined C programs do not invoke UB. A test that happens to return the expected value cannot repair the invalid operation.

## Example: guard before computing

~~~c
#include <limits.h>
#include <stdbool.h>

bool increment(int value, int *out) {
    if (!out || value == INT_MAX) return false;
    *out = value + 1;
    return true;
}
~~~

The guard proves value+1 fits int. An attempted overflow detector that computes value+1 and checks afterward would already have invoked UB. The same order matters for allocation: first prove count<=SIZE_MAX/size, *then* compute bytes.

~~~c
int index = 2;
/* WRONG: int result = index++ + ++index; */
int left = index++;
int right = ++index;
int result = left + right;
~~~

The separated statements establish a sequencing order. Function argument evaluation also has less ordering than many learners assume; avoid expressions where multiple argument side effects depend on which runs first.

## Invalid pointers and byte representations

A pointer can be non-NULL yet dangling. An address that looks aligned may still point outside a valid object or violate effective-type rules. Pointer arithmetic must remain within the permitted array bounds or one-past-the-end. A one-past pointer can act as a sentinel but must not be dereferenced.

Sanitizers catch many violations but not all. Strict warnings, independent tests, review and explicit invariants complement them. Never claim a codebase is UB-free because one compiler's sanitizer passed.

## Investigation worksheet

1. Explain why comparing a+b with a cannot detect signed overflow if the addition already overflowed.
2. Construct a minimal program illustrating unsequenced increments and rewrite it correctly.
3. Distinguish forming a valid one-past pointer from dereferencing it.
4. Describe what happens to borrowed aliases after realloc successfully changes an allocation.
5. Run a disposable overflow demo under UBSan; report the *first* invalid operation.

**Interview checkpoint:** Can compilers optimize based on assumptions of no signed overflow? Yes, because signed overflow is undefined.

**Exit criterion:** You identify the precise invalid operation and change the code so it never occurs.