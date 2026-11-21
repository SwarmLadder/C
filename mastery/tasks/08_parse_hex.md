# Mastery B4 — Strict 32-bit hexadecimal parser

**Level:** Foundations · **Time:** 60–100 minutes · **Implementation:** \`mastery/starter/parse_hex.c\`

## The specification

Implement \`bool parse_u32_hex(const char *text, uint32_t *out)\`. Accept **one to eight** ASCII hexadecimal digits: \`0–9\`, \`a–f\` or \`A–F\`. Do not accept a \`0x\` prefix, a sign, whitespace, separators, an empty string or nine-digit strings, even if they start with zero. On success write the numeric value. On every failure, including NULL pointers, leave the caller's previous output untouched.

Why such a strict grammar? Protocol parsers and configuration tools need to distinguish malformed input from a perfectly valid value zero. The function's input is a valid terminated C string by contract; do not call it with a non-terminated raw buffer. That would require a separate pointer-plus-length API.

## Worked trace

Parsing \`"1aF"\`:
- Start accumulator=0, digits=0.
- \`'1'\` means 1, so accumulator becomes \`0*16 + 1 = 1\`.
- \`'a'\` means 10, so accumulator becomes \`1*16 + 10 = 26\`.
- \`'F'\` means 15, so accumulator becomes \`26*16 + 15 = 431\`.

Parsing \`"FFFFFFFF"\` produces UINT32_MAX. \`"000000000"\` must fail because it has **nine characters**, despite its value fitting. \`"0xFF"\` must fail on \`'x'\`. Never publish intermediate values to \`*out\`: finish validation into a local variable first.

## Correctness and range

Each hexadecimal digit consumes four bits. Eight digits fill at most 32 bits. Before evaluating the shift or multiplication for the ninth digit, reject based on the count. This proves there is no arithmetic overflow within the accepted grammar. Use uint32_t arithmetic, not potentially overflowing signed int arithmetic. The algorithm is O(k) time in the input length until invalid character or overflow-length detection, O(1) space; it can reject after at most nine characters except for very unusual access semantics outside this function's contract.

## Adversarial fixture table

| Input | Result |
| --- | --- |
| \`"0"\` | true, 0 |
| \`"Ff"\` | true, 255 |
| \`"deadBEEF"\` | true, 3,735,928,559 |
| \`"FFFFFFFF"\` | true, UINT32_MAX |
| \`"100000000"\` | false, output unchanged |
| \`"000000000"\` | false, output unchanged |
| \`""\`, \`"+1"\`, \`"0xFF"\`, \`" G"\` | false |

Implement from the starter, run \`make mastery-check TASK=parse_hex\`, then derive an alternative digit-by-digit multiplication guard for a future 64-bit variant.

## Interview and extension

What is the difference between **syntax validation** and **numeric range validation**? Could a length-limited parser accept leading zeros? The answer depends on the specified grammar, not merely the numeric value. Extend the function to accept an explicit byte span without a terminator and return separate syntax/range status codes.

**Review gate:** You can explain why no intermediate result can exceed UINT32_MAX and why invalid text cannot change output.