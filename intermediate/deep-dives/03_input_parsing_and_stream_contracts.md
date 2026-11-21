# Deep Dive 03: Parsing untrusted input without ambiguity

**Outcome:** Distinguish syntax errors, range errors and ordinary end-of-file for a stream parser. **Time:** 110–140 minutes.

## Define the grammar before coding

A decimal integer parser must specify whether it accepts whitespace, plus/minus signs, empty input and trailing characters. If the grammar says one or more ASCII digits with no separators, then " 5", "+5", "5x" and "" must all fail. Do not rely on atoi because it cannot express these distinctions and its overflow behavior is unsuitable for strict validation.

A parser that returns bool and writes an output parameter should preserve output on failure. For multiple fields, parse into temporary locals and commit all outputs only if every field is valid. That gives transactional semantics for the caller.

## Worked unsigned decimal parser

~~~c
#include <stdbool.h>
#include <stdint.h>
#include <stdint.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

bool parse_unsigned(const char *text, unsigned *out) {
    if (!text || !out || text[0] == '\0') return false;
    unsigned value = 0;
    for (size_t i = 0; text[i]; ++i) {
        if (text[i] < '0' || text[i] > '9') return false;
        unsigned digit = (unsigned)(text[i] - '0');
        if (value > (UINT_MAX - digit) / 10U) return false;
        value = value * 10U + digit;
    }
    *out = value;
    return true;
}
~~~

The range guard prevents unsigned wrap before multiplication and addition. It is intentionally strict about ASCII. A source pointer that does not identify a valid null-terminated string remains outside this function's contract.

## Stream semantics

fgetc returns int, not char, because it must represent all unsigned char byte values plus EOF. If it returns EOF, check ferror to distinguish a read failure from successful end-of-file; feof is not true until an attempt to read beyond available input. fwrite may write fewer bytes than requested, so loop until all data is written or an error occurs. fclose may report a buffered write failure.

Do not blindly split a stream into lines using a fixed buffer and assume every logical line fits. Decide whether your parser supports long records, rejects them cleanly, or accumulates them with bounded dynamic storage.

## Parsing tables and CSV

Simple delimiter splitting is insufficient for quoted CSV fields containing delimiters or embedded newlines. A proper CSV state machine distinguishes unquoted fields, quoted fields, escaped double quotes, separators and record boundaries; it must reject malformed terminal quotes. State machines are clearer than a pile of special-case branches.

## Practice

1. Create a table of accepted/rejected strings for parse_unsigned, including UINT_MAX.
2. Extend the parser to report invalid syntax versus overflow without mutating out.
3. Read an input stream one byte at a time and distinguish EOF from ferror.
4. Design states for quoted CSV and trace a field containing a comma.
5. Simulate a short write and explain the loop needed for reliable copying.

**Interview check:** Why cannot errno alone serve as a parse result? Because it may be unchanged on ordinary success or invalid input and needs a specified API usage protocol.

**Exit criterion:** Your parser has an explicit grammar, error model and failure-preservation tests.