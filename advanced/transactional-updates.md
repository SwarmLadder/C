# Transactional updates

A multi-step update needs a single point of commitment. Validate the source, destination and arithmetic before mutating a balance. For batches, stage all changes and publish them together.

## Worked example

```c
unsigned a[4] = {5,0,0,0};
Move batch[] = {{0,1,3},{1,2,4}};
bool ok = settle_four(a,batch,2);
printf("%d %u\n",(int)ok,a[0]);
```

The second transfer needs four after receiving three. The failed batch leaves the opening balance at five.

## Implement and test

Edit [the starter](starter/transactional-updates.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `debit` — Subtract only when funds suffice. Run `make check TASK=debit`.
- `credit` — Add only when the new balance fits. Run `make check TASK=credit`.
- `move_funds` — Reject invalid or equal indices, insufficient funds and destination overflow. Preserve balances on failure. Run `make check TASK=move_funds`.
- `settle_four` — Stage n moves across four accounts. Commit only if every move is valid. Run `make check TASK=settle_four`.

## Independent exercises

1. Return the index of a rejected move.
2. Check the balance sum before and after a successful batch.
3. Test a valid transfer followed by a recipient overflow.
4. Replay a log into a fresh account snapshot.
5. Compare snapshot memory use with a sparse undo log.

## Knowledge check

Does staging a copy make unsynchronized concurrent access safe?

<details><summary>Answer</summary>

No. This contract assumes exclusive access while the batch runs.

</details>

[Worked implementations](solutions/transactional-updates.c) · [Level guide](README.md)
