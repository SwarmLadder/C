# Callbacks

A function pointer lets the caller supply a policy. A context pointer gives the policy its own state. Specify callback order and stopping behavior when a callback can observe those details.

## Worked example

```c
static bool exceeds(int x, void *ctx) {
    const int *limit = ctx;
    return x > *limit;
}
```

With threshold 3, the callback accepts 4 and rejects 3. Define it at file scope and pass the address of the threshold as context.

## Implement and test

Edit [the starter](starter/callbacks.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `count_if` — Count matching elements by invoking test once per element. Run `make check TASK=count_if`.
- `first_if` — Return index of first match or n. Stop testing after the first match. Run `make check TASK=first_if`.
- `apply_each` — Replace each element with f(element). Run `make check TASK=apply_each`.
- `take_while` — Count the matching prefix only. Run `make check TASK=take_while`.

## Independent exercises

1. Implement any-match with short circuiting.
2. Count calls in a no-match search.
3. Pass a range struct as callback context.
4. Filter into a separate destination.
5. Transform positive values only.

## Knowledge check

When does a callback context pointer become invalid?

<details><summary>Answer</summary>

When its backing object ends its lifetime. A synchronous walker may borrow caller storage for the duration of the call.

</details>

[Worked implementations](solutions/callbacks.c) · [Level guide](README.md)
