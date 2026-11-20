# Loop invariants

Choose what the accumulator means before writing the loop. To sum digits, add the final digit and remove it by dividing by ten. Each iteration reduces the remaining number.

## Worked example

```c
unsigned n = 709;
while (n) { printf("%u ", n%10); n /= 10; }
```

The digits appear as 9, 0, 7. Each division removes one digit.

## Implement and test

Edit [the starter](starter/loop-invariants.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `digit_sum` — Sum decimal digits. Run `make check TASK=digit_sum`.
- `digit_count` — Count digits, including the zero in 0. Run `make check TASK=digit_count`.
- `gcd_of` — Use Euclidean remainder. Define gcd(0,0) as 0. Run `make check TASK=gcd_of`.
- `is_prime` — Recognize primes without multiplying candidate factors. Run `make check TASK=is_prime`.

## Independent exercises

1. Trace gcd(42,30) by hand.
2. Count trailing decimal zeros of a positive integer.
3. Reverse the digits of a number below 10,000.
4. Find the smallest prime greater than 30.
5. Write a factorial function that reports overflow.

## Knowledge check

Why use i <= n/i instead of i*i <= n?

<details><summary>Answer</summary>

Squaring a large candidate can overflow before the comparison.

</details>

[Worked implementations](solutions/loop-invariants.c) · [Level guide](README.md)
