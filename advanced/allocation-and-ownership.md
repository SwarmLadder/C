# Allocation and ownership

An owning pointer needs one matching free. Separate allocation failure from a valid result and guard size multiplication. realloc may move a block, so preserve the original pointer until success.

## Worked example

```c
Vector v = {0};
if (push_value(&v,7)) printf("%d\n",v.data[0]);
release_values(&v);
```

Append acquires storage. Release returns it and leaves the vector empty.

## Implement and test

Edit [the starter](starter/allocation-and-ownership.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `clone_values` — Allocate an independent copy. Return NULL on zero length, excessive size, or allocation failure. Run `make check TASK=clone_values`.
- `reserve_values` — Grow capacity to at least need, preserving length and contents. Keep all fields intact on failure. Run `make check TASK=reserve_values`.
- `push_value` — Append one value. Grow geometrically where possible. Return false with original state on allocation failure. Run `make check TASK=push_value`.
- `release_values` — Free owned storage and set all fields to zero so repeated release is valid. Run `make check TASK=release_values`.

## Independent exercises

1. Add a pop operation that preserves capacity.
2. Implement deep cloning of a Vector.
3. Count reallocations across 1,024 appends.
4. Factor allocation behind a callback for deterministic failure tests.
5. Test a failed reserve with a live nonempty vector.

## Knowledge check

Why assign realloc to a temporary?

<details><summary>Answer</summary>

On failure the old allocation still belongs to the caller. Direct assignment would lose its address.

</details>

[Worked implementations](solutions/allocation-and-ownership.c) · [Level guide](README.md)
