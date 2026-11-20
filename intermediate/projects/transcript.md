# Line-numbered transcript

A reviewer needs a numbered transcript for an input stream with unknown length.

## Deliverable

Prefix each logical line with its one-based number and a space. Preserve existing newlines and final unterminated text. Empty input produces nothing. Report read or immediate write errors. Assume line numbers fit size_t.

1. Choose a representative input, an empty or smallest valid input, and a boundary case. Predict the exact output for each.
2. Implement `transcript` in [the starter](../starter/transcript.c). Check the required behavior with `make check TASK=transcript`.
3. Add a starting line-number option and test blank lines, very long lines and a missing final newline.

Review your implementation against [the worked project](../solutions/transcript.c). The extension is assessed by demonstration and code review.
