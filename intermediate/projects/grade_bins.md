# Grade histogram

A teacher imports numeric grades. Build a report with separate validation and aggregation stages.

## Deliverable

Validate scores 0–100. Fill five counts for 0–59, 60–69, 70–79, 80–89 and 90–100. Invalid input preserves all five outputs.

1. Choose a representative input, an empty or smallest valid input, and a boundary case. Predict the exact output for each.
2. Implement `grade_bins` in [the starter](../starter/grade_bins.c). Check the required behavior with `make check TASK=grade_bins`.
3. Render the five bands as a text histogram and check that their counts sum to the class size.

Review your implementation against [the worked project](../solutions/grade_bins.c). The extension is assessed by demonstration and code review.
