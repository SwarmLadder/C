# Mastery lab B2 — Strict decimal-to-u32 parser

**Difficulty:** foundational / security. **Target:** parse_u32_strict. **Suggested time:** 60–90 minutes.

## Contract and grammar

Accept only one or more ASCII characters 0 through 9. No signs, spaces, decimal points or trailing bytes are valid. Produce the mathematically correct uint32_t value in the inclusive range 0 to UINT32_MAX. Return false on invalid syntax, overflow or NULL inputs, and leave *out unchanged on failure.

This apparently small function models real protocol parsing. A parser that uses atoi often cannot distinguish valid zero, malformed syntax and out-of-range input. A secure parser checks each byte and its arithmetic range before updating the accumulator.

## Loop invariant

After k valid digits, the temporary accumulator equals the mathematical value of the first k characters and fits uint32_t. Before appending digit d, prove accumulator <= (UINT32_MAX-d)/10. Only then calculate accumulator*10+d. A failure returns immediately without publishing the temporary accumulator.

## Cases to test

- "0" → 0; "0001" → 1; "4294967295" → UINT32_MAX.
- Empty text, "-1", "+1", " 1", "1 " and "12x" all fail.
- "4294967296" fails for overflow.
- A very long digit string must reject without arithmetic wrap.
- NULL input and NULL output fail.

Implement the starter in mastery/starter/parse_decimal.c:

~~~sh
make mastery-check TASK=parse_decimal
~~~

## Extension

Change the API to return a status enum distinguishing empty, invalid character and overflow. Preserve the output for every error. Next, accept an explicit pointer-plus-length span and test a non-NUL-terminated byte buffer without ever calling strlen.

**Proof prompt:** Why is the temporary accumulator always representable after every accepted digit? Prove it inductively from the guard and the update equation.

**Interview follow-up:** Why does a pointer-plus-length API better match network input than an assumed C string? Network data may contain zeros and may not be terminated.