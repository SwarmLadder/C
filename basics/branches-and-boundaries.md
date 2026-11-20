# Branches and boundaries

Put exceptional cases before broader ranges. Check both sides of each boundary. A fare for ages under six must distinguish five from six.

## Worked example

```c
unsigned age = 17;
if (age < 6) puts("free");
else if (age < 18) puts("student");
else puts("adult");
```

The second branch is reached only after the first fails. Repeat with ages 5, 6 and 18.

## Implement and test

Edit [the starter](starter/branches-and-boundaries.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `sign_of` — Map negative, zero, positive to -1, 0, 1. Run `make check TASK=sign_of`.
- `leap_year` — Apply Gregorian leap-year rules. Run `make check TASK=leap_year`.
- `fare` — Charge 0 below age 6, 2 up to 17, 3 from 65, otherwise 5. Run `make check TASK=fare`.
- `middle` — Return the median of three ints without adding them. Run `make check TASK=middle`.

## Independent exercises

1. Validate a month numbered 1 to 12.
2. Classify coordinates into quadrants with a separate axis case.
3. Extend fare with a weekend price cap.
4. Write a truth table for divisibility by 4, 100 and 400.
5. Test median on all permutations of three distinct values.

## Knowledge check

Why avoid a+b+c when finding the median?

<details><summary>Answer</summary>

The sum can overflow even when all three inputs and the answer fit.

</details>

[Worked implementations](solutions/branches-and-boundaries.c) · [Level guide](README.md)
