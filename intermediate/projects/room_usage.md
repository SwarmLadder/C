# Room bookings

A community center receives unsorted bookings for one room. Validate and normalize its occupied hours.

## Deliverable

Input spans are half-open minutes of one day. Reject empty, reversed or out-of-day spans without changing output. Return unique occupied minutes.

1. Choose a representative input, an empty or smallest valid input, and a boundary case. Predict the exact output for each.
2. Implement `room_usage` in [the starter](../starter/room_usage.c). Check the required behavior with `make check TASK=room_usage`.
3. Emit contiguous free spans and test adjacent bookings at midnight.

Review your implementation against [the worked project](../solutions/room_usage.c). The extension is assessed by demonstration and code review.
