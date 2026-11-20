# Records and reports

A struct groups fields that belong to one observation. Read through a const pointer when producing a report. Keep ties deterministic by replacing a winner only on a strictly better score.

## Worked example

```c
Point stop = {.x=-2, .y=3};
const Point *view = &stop;
printf("%d\n", view->y);
```

The pointer borrows the record. The arrow reads its y field and prints 3.

## Implement and test

Edit [the starter](starter/records-and-reports.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `point_total` — Sum the two int16_t coordinates in a long. Run `make check TASK=point_total`.
- `on_axis` — Decide whether either coordinate is zero. Run `make check TASK=on_axis`.
- `best_point` — Return index of first greatest coordinate sum, or n if empty. Run `make check TASK=best_point`.
- `enclosed` — Count points in the inclusive square from -limit to limit on both axes. Negative limit means empty. Run `make check TASK=enclosed`.

## Independent exercises

1. Reflect a point across the x-axis with range checking.
2. Report the first point on an axis.
3. Find the bounding rectangle of a nonempty route.
4. Compare two points for fieldwise equality.
5. Print a table of points and coordinate sums.

## Knowledge check

Why avoid comparing structs with memcmp for field equality?

<details><summary>Answer</summary>

Padding bytes can differ even when the corresponding fields are equal.

</details>

[Worked implementations](solutions/records-and-reports.c) · [Level guide](README.md)
