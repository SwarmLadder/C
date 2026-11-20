# Circular queues

For a fixed-capacity ring, track the first occupied index and the number of live elements. Wrapping indices lets a queue reuse storage at the front. Define empty and full by length.

## Worked example

```c
Ring q = {.head=7};
ring_put(&q,10); ring_put(&q,20);
int first;
if(ring_get(&q,&first)) printf("%d\n",first);
```

Ten occupies physical index 7 and twenty index 0. Removing ten advances the head to 0.

## Implement and test

Edit [the starter](starter/circular-queues.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `ring_put` — Append to an eight-slot ring; reject a full queue. Run `make check TASK=ring_put`.
- `ring_get` — Remove oldest value. On empty leave output unchanged. Run `make check TASK=ring_get`.
- `ring_at` — Read by logical index without consuming. Reject indices outside the live range. Run `make check TASK=ring_at`.
- `ring_drop` — Discard at most n oldest items, returning the number removed. Run `make check TASK=ring_drop`.

## Independent exercises

1. Copy out all items in FIFO order.
2. Implement peek-last without mutating the ring.
3. Compare 100 alternating operations with a simple array oracle.
4. Add batch insertion with all-or-nothing semantics.
5. Implement overwrite-oldest as a separate policy.

## Knowledge check

What distinguishes full from empty when the next tail index equals head?

<details><summary>Answer</summary>

The live length is eight for full and zero for empty.

</details>

[Worked implementations](solutions/circular-queues.c) · [Level guide](README.md)
