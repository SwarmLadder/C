# Trail report

A hiking club records elevation at each checkpoint. Build a summary the club can use to compare two walks. Manually trace 4, 8, 3, 8 before coding.

## Deliverable

Return total ascent and first highest index. Empty input returns {0,0}. Assume total ascent fits uint64_t.

1. Choose a representative input, an empty or smallest valid input, and a boundary case. Predict the exact output for each.
2. Implement `trail_report` in [the starter](../starter/trail_report.c). Check the required behavior with `make check TASK=trail_report`.
3. Extend the report with total descent and prove that ascent minus descent equals final minus initial elevation.

Review your implementation against [the worked project](../solutions/trail_report.c). The extension is assessed by demonstration and code review.
