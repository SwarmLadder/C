# Event replay

An event buffer has room for only the most recent eight readings. Produce its chronological contents.

## Deliverable

Write the latest at most eight readings, oldest first, to a disjoint eight-slot output. Return their count. Model the incoming data as a stream using a circular buffer.

1. Choose a representative input, an empty or smallest valid input, and a boundary case. Predict the exact output for each.
2. Implement `replay_recent` in [the starter](../starter/replay_recent.c). Check the required behavior with `make check TASK=replay_recent`.
3. Expose a streaming append interface and test that splitting the same trace across calls leaves an identical report.

Review your implementation against [the worked project](../solutions/replay_recent.c). The extension is assessed by demonstration and code review.
