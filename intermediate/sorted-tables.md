# Sorted tables

In sorted data a comparison can discard an entire half of the search interval. Use a half-open interval [lo, hi). When both bounds meet, their location is a valid insertion position.

## Worked example

```c
int a[] = {2,4,4,9};
size_t first = lower_slot(a,4,4), end = upper_slot(a,4,4);
printf("%zu\n", end-first);
```

The matching indices are 1 and 2. Subtracting half-open bounds gives two occurrences.

## Implement and test

Edit [the starter](starter/sorted-tables.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `lower_slot` — Find first index at least key in sorted input in logarithmic time. Run `make check TASK=lower_slot`.
- `upper_slot` — Find first index strictly greater than key in sorted input in logarithmic time. Run `make check TASK=upper_slot`.
- `insertion_sort` — Sort ascending in place by inserting one element into a sorted prefix at a time. Run `make check TASK=insertion_sort`.
- `unique_sorted` — Compact adjacent equal values of sorted input. Return distinct count. Run `make check TASK=unique_sorted`.

## Independent exercises

1. Count duplicates using two partition points.
2. Find the predecessor of an absent key.
3. Merge two sorted arrays into a disjoint destination.
4. Count comparisons for 64 sorted entries.
5. Generate sorted inputs with every key equal.

## Knowledge check

What bounds change when v[mid] equals key in lower-bound search?

<details><summary>Answer</summary>

hi becomes mid because an earlier equal key may exist.

</details>

[Worked implementations](solutions/sorted-tables.c) · [Level guide](README.md)
