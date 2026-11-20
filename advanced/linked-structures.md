# Linked structures

Track the link that leads to the current node. For removal at the head, that link belongs to the caller. For removal in the middle it belongs to the previous node. None of these operations owns the nodes themselves.

## Worked example

```c
Node tail = {2,NULL}, head = {1,&tail};
for (const Node *p=&head; p; p=p->next) printf("%d ",p->value);
```

The traversal prints 1 then 2. These nodes have automatic storage and must never be passed to free.

## Implement and test

Edit [the starter](starter/linked-structures.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `list_len` — Count nodes in an acyclic list. Run `make check TASK=list_len`.
- `reverse_list` — Reverse links in place and return the new head. Run `make check TASK=reverse_list`.
- `detach` — Unlink the first matching node and clear its next link. Return NULL if missing. Run `make check TASK=detach`.
- `has_cycle` — Detect a cycle using constant additional storage. Run `make check TASK=has_cycle`.

## Independent exercises

1. Find the middle node using two pointers.
2. Return the last node without allocating.
3. Splice two disjoint acyclic lists.
4. Test removing the only node.
5. Find the entry node of a cycle.

## Knowledge check

Why save next before reversing a link?

<details><summary>Answer</summary>

It is the only remaining path to the unprocessed suffix.

</details>

[Worked implementations](solutions/linked-structures.c) · [Level guide](README.md)
