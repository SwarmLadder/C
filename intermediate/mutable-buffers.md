# Mutable buffers

A caller supplies a destination and its capacity. For C strings the terminator needs one byte too. A destination of capacity three fits two text bytes and one terminator.

## Worked example

```c
char b[5] = "abcd";
memmove(b+1,b,3);
puts(b);
```

The regions overlap. memmove preserves the original three source bytes, giving aabc. Include string.h.

## Implement and test

Edit [the starter](starter/mutable-buffers.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `copy_text` — Copy a string between disjoint buffers including terminator. Preserve destination on failure. Run `make check TASK=copy_text`.
- `reverse_ints` — Reverse elements in place. Run `make check TASK=reverse_ints`.
- `compact` — Remove skip values in place, keeping order. Return new logical length. Run `make check TASK=compact`.
- `erase_at` — Delete a valid element by shifting successors left. Ignore the final storage slot. Run `make check TASK=erase_at`.

## Independent exercises

1. Compact runs of repeated values.
2. Insert one item when capacity permits.
3. Rotate an array by one position.
4. Copy a suffix into a disjoint character buffer.
5. Demonstrate a successful exact-fit copy.

## Knowledge check

Why use memmove when shifting elements?

<details><summary>Answer</summary>

The source and destination can overlap.

</details>

[Worked implementations](solutions/mutable-buffers.c) · [Level guide](README.md)
