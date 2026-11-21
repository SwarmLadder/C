# Mastery lab B1 — Checked signed addition

**Difficulty:** foundational, but safety critical. **Target:** checked_add_i32 in mastery/include/mastery.h. **Suggested time:** 45–75 minutes.

## The problem

Implement a function that adds two int32_t values only when their mathematical sum is representable as int32_t. Return true and store the result on success; return false and leave the existing output untouched on overflow or a NULL output pointer. Do not perform a signed addition that may overflow. C signed overflow is undefined behavior; checking it after computing the sum is too late.

## Worked reasoning, without the answer

If b is positive, a must be at most INT32_MAX-b. If b is negative, a must be at least INT32_MIN-b. These inequalities use representable subtraction values. Once the guard succeeds, the final addition is safe. This is not equivalent to casting both numbers to unsigned and hoping the result can be interpreted as signed.

## Examples and boundary tests

- 4 + 5 succeeds and writes 9.
- INT32_MAX + 1 fails and retains the previous output.
- INT32_MIN + (-1) fails and retains the previous output.
- INT32_MIN + INT32_MAX succeeds and writes -1.
- A NULL output pointer fails without dereferencing it.

## Implementation strategy

Read the declaration in mastery/include/mastery.h. Implement the function in mastery/starter/checked_add.c and run:

~~~sh
make mastery-check TASK=checked_add
~~~

Trace the positive, negative and zero branches. Write a test table using b={-1,0,1} and a near both limits. Failure preservation is part of correctness, not an optional API convention.

## Stretch challenge

Write checked subtraction. Explain why implementing subtraction as addition of -b can itself overflow when b is INT32_MIN. Then implement a checked multiplication routine that correctly rejects INT32_MIN * -1.

**Proof prompt:** Show that neither bound test can overflow and that successful execution only reaches a representable addition.

**Interview follow-up:** Why is signed integer overflow not guaranteed to wrap, even on two's-complement CPUs? Because C's abstract machine does not define signed overflow as modular arithmetic.