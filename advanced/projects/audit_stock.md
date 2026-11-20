# Inventory audit

A stockroom ships units between bins. Reconcile a batch of movements and return a reproducible audit record.

## Deliverable

Stage four bins. Reject invalid or equal indices, insufficient stock or recipient overflow. On failure record first bad index and preserve bins. On success commit bins and set bad to n.

1. Choose a representative input, an empty or smallest valid input, and a boundary case. Predict the exact output for each.
2. Implement `audit_stock` in [the starter](../starter/audit_stock.c). Check the required behavior with `make check TASK=audit_stock`.
3. Add an audit summary with opening and closing totals and verify conservation across dependent transfers.

Review your implementation against [the worked project](../solutions/audit_stock.c). The extension is assessed by demonstration and code review.
