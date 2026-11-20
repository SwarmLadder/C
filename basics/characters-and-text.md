# Characters and text

A C string ends at the first zero byte. Walking it counts bytes, which can differ from the number of displayed characters. The exercises here use ASCII bytes and leave other bytes unchanged.

## Worked example

```c
char text[] = "ab";
printf("%zu %zu\n", sizeof text, strlen(text));
```

The array occupies three bytes. strlen returns two because it stops at the terminator. Include string.h.

## Implement and test

Edit [the starter](starter/characters-and-text.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `ascii_digit` — Recognize decimal digits. Run `make check TASK=ascii_digit`.
- `ascii_lower` — Lowercase ASCII A–Z only. Run `make check TASK=ascii_lower`.
- `byte_length` — Count bytes before the terminator. Run `make check TASK=byte_length`.
- `words` — Count runs separated by ASCII spaces or tabs. Run `make check TASK=words`.

## Independent exercises

1. Count uppercase ASCII bytes.
2. Trim leading spaces by returning a borrowed pointer.
3. Count a chosen byte in a string.
4. Extend word counting to include newline separators.
5. Compare the byte counts of an empty string and a one-space string.

## Knowledge check

Does an embedded zero byte end a C string?

<details><summary>Answer</summary>

Yes. Bytes stored after it are outside that string.

</details>

[Worked implementations](solutions/characters-and-text.c) · [Level guide](README.md)
