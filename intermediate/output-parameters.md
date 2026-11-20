# Output parameters

Use a status result when every numeric value is a possible answer. Compute in local variables first. Assign through the output pointer only after validating the whole request.

## Worked example

```c
unsigned answer = 19;
if (safe_add(UINT_MAX,1,&answer)) puts("updated");
printf("%u\n", answer);
```

The failed addition preserves 19. Include limits.h for UINT_MAX.

## Implement and test

Edit [the starter](starter/output-parameters.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `safe_add` — Store a+b only when representable. Run `make check TASK=safe_add`.
- `safe_mul` — Store a*b only when representable. Run `make check TASK=safe_mul`.
- `range_of` — Write min and max to distinct outputs. Leave both intact if empty. Run `make check TASK=range_of`.
- `div_parts` — Write quotient and remainder to distinct outputs only when d is nonzero. Run `make check TASK=div_parts`.

## Independent exercises

1. Add checked subtraction.
2. Return minimum with its first index.
3. Write tests that preserve sentinel outputs on failure.
4. Implement checked multiply-then-add.
5. Specify whether two output pointers may alias.

## Knowledge check

Why check overflow before multiplication?

<details><summary>Answer</summary>

The product may have already wrapped by the time it is examined.

</details>

[Worked implementations](solutions/output-parameters.c) · [Level guide](README.md)
