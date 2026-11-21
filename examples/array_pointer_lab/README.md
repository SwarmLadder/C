# Practical C17 lab: arrays and pointers

Run `make array-pointer-reference` to compile and test the completed C implementation. Run `make array-pointer-practice` to compile and test the unfinished learner implementation (expected to fail until completed). This lab is separate from the 81 existing workshop functions and 12 mastery APIs.

## Challenge: stable zero compaction

Implement `void move_zeros(int *values, size_t n)` with:
- O(n) time and O(1) additional memory
- all zeros at the end, nonzero relative order preserved
- legal empty input `values == NULL && n == 0`
- for nonempty input, `values` points to at least `n` modifiable ints

Example: `[0, 5, 0, 3, 12, 0, 7]` → `[5, 3, 12, 7, 0, 0, 0]`.

Implement in `starter.c`. Trace the read and write pointers on paper. Check all-zero, no-zero, negative and empty cases. The finished example is `reference.c`, to be read after the attempt. Neither function allocates memory or returns a value.

Cross-check the equivalent Python challenge in the `SwarmLadder/Data-Structures-Algorithms` repository under `labs/two_pointers`.

To run without changing the repository's existing Makefile:

```sh
cc -std=c17 -Wall -Wextra -Werror -pedantic examples/array_pointer_lab/reference.c examples/array_pointer_lab/test.c -o /tmp/array_pointer_test
/tmp/array_pointer_test
```
