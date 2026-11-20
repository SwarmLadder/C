# Bit sets

An unsigned bit mask represents a small set of indices. The shift count must be smaller than the width of the promoted left operand. Validate the index before computing its mask.

## Worked example

```c
uint32_t mask = UINT32_C(1)<<3;
printf("%u\n",(unsigned)((mask>>3)&1u));
```

Index three has numeric value eight. Moving that bit to position zero reveals membership.

## Implement and test

Edit [the starter](starter/bit-sets.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `bit_member` — Test membership at indices 0–31; return false elsewhere. Run `make check TASK=bit_member`.
- `bit_toggle` — Toggle a valid bit and report success. Invalid indices preserve the mask. Run `make check TASK=bit_toggle`.
- `population` — Count set bits without a lookup table. Run `make check TASK=population`.
- `rotate_left` — Rotate bits left by n modulo 32. Run `make check TASK=rotate_left`.

## Independent exercises

1. Compute the symmetric difference of two sets.
2. Extract the lowest set bit.
3. List members in increasing order.
4. Pack two four-bit fields into one byte.
5. Test that 32 single-step rotations restore the input.

## Knowledge check

Why special-case zero in a 32-bit rotation?

<details><summary>Answer</summary>

The complementary shift would otherwise be 32, which is invalid on a 32-bit operand.

</details>

[Worked implementations](solutions/bit-sets.c) · [Level guide](README.md)
