# Parsing fields

A parser should say which syntax it accepts before converting anything. Read digits one by one, and distinguish invalid input from a valid zero. Empty fields remain significant.

## Worked example

```c
const char *row = "rate=12";
const char *sep = strchr(row, 61);
if (sep) printf("%td %s\n", sep-row, sep+1);
```

The separator is four bytes from the start of the row. The remaining string is 12. Include string.h.

## Implement and test

Edit [the starter](starter/parsing-fields.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `decimal_byte` — Parse one or more ASCII digits into 0–255. Reject signs and spaces. Preserve output on failure. Run `make check TASK=decimal_byte`.
- `hex_digit` — Return value of one ASCII hex digit, or -1. Run `make check TASK=hex_digit`.
- `columns` — Count tab-separated fields. Even an empty line has one field. Run `make check TASK=columns`.
- `key_span` — Find first equals sign. Require a nonempty preceding key; preserve output on failure. Run `make check TASK=key_span`.

## Independent exercises

1. Decode two hex digits to one byte.
2. Report the first invalid byte position.
3. Accept optional surrounding spaces explicitly.
4. Return a borrowed pointer to a setting value.
5. Check equal column counts across three rows.

## Knowledge check

Why reject 256 immediately in a decimal byte parser?

<details><summary>Answer</summary>

Appending more decimal digits cannot bring it back into range.

</details>

[Worked implementations](solutions/parsing-fields.c) · [Level guide](README.md)
