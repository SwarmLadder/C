# Binary records

A wire format defines byte order independently of machine layout. Decode headers byte by byte, and validate lengths before taking a view into the payload. A view borrows its input.

## Worked example

```c
uint8_t wire[] = {0,2,65,66};
Slice in = {wire,sizeof wire}, payload;
if(next_frame(&in,&payload)) printf("%zu %zu\n",payload.len,in.len);
```

The payload has two bytes and the input has none left. The backing bytes still belong to wire.

## Implement and test

Edit [the starter](starter/binary-records.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `read_be16` — Read two big-endian bytes. Run `make check TASK=read_be16`.
- `write_le32` — Write four bytes least significant first. Run `make check TASK=write_le32`.
- `next_frame` — Consume a two-byte big-endian length and its payload. On truncation leave both distinct slice descriptors unchanged. Run `make check TASK=next_frame`.
- `check_byte` — Return the additive complement modulo 256. Run `make check TASK=check_byte`.

## Independent exercises

1. Encode a length-prefixed frame into caller storage.
2. Decode a zero-length payload followed by another frame.
3. Find the offset of the first truncated record.
4. Add checksum verification to a frame reader.
5. Document how long a returned payload view is valid.

## Knowledge check

Why avoid copying a C struct directly as a wire header?

<details><summary>Answer</summary>

Padding, member layout and integer byte order can depend on the implementation.

</details>

[Worked implementations](solutions/binary-records.c) · [Level guide](README.md)
