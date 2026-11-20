# Clocks and units

Compute the quotient for complete units and the remainder for the part left over. A 125-second timer shows 2 minutes and 5 seconds. Widen before multiplying two small integer types.

## Worked example

```c
unsigned s = 7325;
printf("%u:%02u:%02u\n", s/3600, s/60%60, s%60);
```

The remaining 125 seconds supply the last two fields. The display reads 2:02:05.

## Implement and test

Edit [the starter](starter/clocks-and-units.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `whole_minutes` — Return complete minutes. Run `make check TASK=whole_minutes`.
- `clock_seconds` — Return the seconds field of a timer. Run `make check TASK=clock_seconds`.
- `billed_hours` — Round minutes up to full hours without overflowing. Run `make check TASK=billed_hours`.
- `tile_area` — Calculate area for any two 16-bit dimensions. Run `make check TASK=tile_area`.

## Independent exercises

1. Split 9,007 seconds into hours, minutes and seconds.
2. Write the inverse conversion for times within one day.
3. Build a table for 0, 59, 60 and 61 seconds.
4. Change billing to 15-minute units.
5. Explain why adding 59 before division can fail.

## Knowledge check

Why does 59 / 60 give zero here?

<details><summary>Answer</summary>

Both operands are integers and the positive fractional part is discarded.

</details>

[Worked implementations](solutions/clocks-and-units.c) · [Level guide](README.md)
