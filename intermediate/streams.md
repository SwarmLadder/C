# Streams

fgetc returns int so that EOF and every byte are distinguishable. Process one byte at a time when input size is unknown. Check the error indicator separately from normal end of input.

## Worked example

```c
int c;
while ((c=fgetc(stdin)) != EOF)
    if (c==10) puts("line ended");
```

An a followed by newline prints one message. An unterminated final a produces none.

## Implement and test

Edit [the starter](starter/streams.c). Read the function declarations in [course.h](../include/course.h). Run these commands from the repository root.

- `first_byte` — Read and return one byte as int, or EOF. Run `make check TASK=first_byte`.
- `newlines` — Count newline bytes through EOF on a readable error-free input stream. Run `make check TASK=newlines`.
- `emit_line` — Write a string followed by a newline. Report any immediate write failure. Run `make check TASK=emit_line`.
- `copy_stream` — Copy through EOF and detect read and immediate write errors. Flushing is the caller’s responsibility. Run `make check TASK=copy_stream`.

## Independent exercises

1. Count a final unterminated line as a logical line.
2. Copy at most N bytes.
3. Report the first differing byte in two streams.
4. Translate tabs into single spaces while copying.
5. Check flush errors separately from write errors.

## Knowledge check

Why store fgetc in int before testing EOF?

<details><summary>Answer</summary>

Narrowing first can lose the distinction between a byte value and EOF.

</details>

[Worked implementations](solutions/streams.c) · [Level guide](README.md)
