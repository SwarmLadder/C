# Sequences and windows

An array argument carries no length. Pass the number of elements separately. A two-element window starts at index 1 when comparing the current value with its predecessor.

## Worked example

```c
int a[] = {4,4,9};
for (size_t i=1; i<3; ++i) printf("%d -> %d\n", a[i-1], a[i]);
```

Three samples yield two pairs. Only the second rises.

## Implement and test

Edit [the starter](starter/sequences-and-windows.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `negatives` — Count strictly negative samples. Run `make check TASK=negatives`.
- `rises` — Count strictly rising adjacent steps. Run `make check TASK=rises`.
- `first_index` — Return first matching index, or n. Run `make check TASK=first_index`.
- `longest_run` — Return longest consecutive run of key. Run `make check TASK=longest_run`.

## Independent exercises

1. Find the last matching index.
2. Count the number of plateaus between adjacent readings.
3. Return the first position of the longest run.
4. Check whether a sequence is strictly decreasing.
5. Build tests for alternating signs and all-equal input.

## Knowledge check

Why can n represent a missing index?

<details><summary>Answer</summary>

Every valid index is strictly less than n.

</details>

[Worked implementations](solutions/sequences-and-windows.c) · [Level guide](README.md)
