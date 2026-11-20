# Meter invoice

A maker space charges for time in blocks. Produce a deterministic bill grouped by visits.

## Deliverable

Each visit gets five free minutes. Charge 3 credits per started 15-minute block thereafter. Assume the total fits.

1. Choose a representative input, an empty or smallest valid input, and a boundary case. Predict the exact output for each.
2. Implement `meter_bill` in [the starter](../starter/meter_bill.c). Check the required behavior with `make check TASK=meter_bill`.
3. Produce an itemized invoice and test where rounding each visit differs from rounding the weekly total.

Review your implementation against [the worked project](../solutions/meter_bill.c). The extension is assessed by demonstration and code review.
