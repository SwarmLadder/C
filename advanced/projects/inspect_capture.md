# Telemetry frame index

An instrument emits length-prefixed binary readings. Verify a whole capture before publishing its record count.

## Deliverable

Walk two-byte big-endian length-prefixed frames without allocation. Count empty frames. Reject trailing fragments and preserve count on error.

1. Choose a representative input, an empty or smallest valid input, and a boundary case. Predict the exact output for each.
2. Implement `inspect_capture` in [the starter](../starter/inspect_capture.c). Check the required behavior with `make check TASK=inspect_capture`.
3. Build a zero-copy index of frame offsets; report the starting offset of a rejected frame.

Review your implementation against [the worked project](../solutions/inspect_capture.c). The extension is assessed by demonstration and code review.
