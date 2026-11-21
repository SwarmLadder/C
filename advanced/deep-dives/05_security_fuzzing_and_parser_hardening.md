# Deep Dive 05 — Security review and fuzzing for C

**Outcome:** Harden byte parsers against invalid lengths, arithmetic wrap and adversarial input. **Time:** 150 minutes.

## Validate before you access

A robust decoder maintains offset<=size and checks field_len<=size-offset before accessing a field. The more tempting condition offset+field_len<=size can overflow, potentially authorizing an out-of-range access. Use subtraction after checking the offset is in range.

~~~c
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool advance(size_t size, size_t *offset, size_t count) {
    if (!offset || *offset > size || count > size - *offset)
        return false;
    *offset += count;
    return true;
}
~~~

This function only manages an offset; a caller must still provide a valid actual byte array when reading. On failure the old offset is retained. In a full record parser, stage decoded fields in temporary variables and copy them to the output only after all syntax, length and checksum checks succeed.

## Threat model the entire chain

Untrusted packet length can influence allocation, memcpy, string formatting and logging. Check multiplication before allocating count*size, additions before buffer growth and all length-prefixed fields before dereferencing. Do not pass untrusted data as a printf format string. Choose a maximum permitted message length to prevent resource-exhaustion attacks even when an input is technically representable.

An API that "usually" receives trusted local files still needs error handling: files can be truncated, corrupted, replaced or malicious. Explicitly state what data the caller promises to supply and what input the function itself validates.

## Fuzzing and property checks

Generate many small valid and invalid inputs under sanitizers. Seed truncated messages at every boundary, empty packets, repeated delimiters and bytes 0x00 and 0xff. Check properties in addition to concrete expected outputs: failed parsing never modifies caller state; decode(encode(x))==x; reported lengths never exceed capacities; the same input yields the same result.

Differential testing compares a fast implementation with an independent simple oracle, reducing the risk of copying the same bug into both test and code. A passing fuzz run improves confidence but cannot prove all executions safe.

## Practice

1. Audit one size addition and one multiplication for wrap.
2. Generate deterministic random truncations of a six-byte packet; verify no invalid memory accesses.
3. Test output preservation on every decoder failure path.
4. Explain how a percent symbol in untrusted input becomes dangerous when used as a format string.
5. List what AddressSanitizer, UBSan and fuzzing each do *not* guarantee.

**Interview checkpoint:** Why check len<=size-offset instead of offset+len<=size? The subtraction form avoids overflow after offset bounds are established.

**Exit criterion:** Every untrusted length is checked before allocation, indexing, pointer arithmetic or copying.