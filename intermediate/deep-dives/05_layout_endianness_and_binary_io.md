# Deep Dive 05: Alignment, byte order and binary protocol design

**Outcome:** Encode portable binary records without depending on compiler-specific struct layout. **Time:** 110–140 minutes.

## Object layout is not a wire format

A struct can have internal and trailing padding due to alignment. sizeof(struct) may exceed the sum of member widths. Numeric fields also have machine-dependent byte order. Writing an entire struct with fwrite is only a safe local memory-image operation under very narrow assumptions; it is *not a stable network or disk format*.

Define a protocol in bytes instead. A record with 16-bit version, 32-bit sequence and 8-bit kind occupies exactly seven bytes if the protocol says so. Encode and decode each field using shifts and masks on unsigned integer types.

~~~c
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

bool decode_be32(const uint8_t *buf, size_t n, uint32_t *out) {
    if (!buf || !out || n < 4) return false;
    uint32_t value = ((uint32_t)buf[0] << 24) |
                     ((uint32_t)buf[1] << 16) |
                     ((uint32_t)buf[2] << 8) |
                     (uint32_t)buf[3];
    *out = value;
    return true;
}
~~~

Casting before shifting ensures operands have enough unsigned width for the shift. The function does not overread a short buffer and preserves out on failure. Document whether n may exceed four and whether trailing bytes are ignored.

## Alignment and strict aliasing

Do not cast an arbitrary byte pointer to uint32_t* and dereference it to decode a packet. The pointer may be insufficiently aligned, violate effective-type constraints or read the wrong endian representation. memcpy can safely move bytes between object representations when the target object is suitably typed, but the numeric meaning still depends on endianness unless you decode explicitly.

A flexible array member at the end of a struct can represent variable-size storage, but correct allocation requires checked header+payload size arithmetic and alignment.

## Failure-first parsing

Inspect the buffer length before reading any field, then check magic/version, then payload size, then checksum or other consistency rules. If decoding an entire record fails, do not partially update outputs. A caller may assume an earlier result still exists when an invalid packet arrives.

## Practice

1. Implement a seven-byte encoder and decoder, testing all fields at their maximum values.
2. Inspect sizeof and offsetof for a struct on two toolchains; do not assume they match the protocol length.
3. Decode from a pointer one byte into a buffer; show why bytewise decoding is alignment-safe.
4. Explain why memcpy does not automatically solve endianness.
5. Test truncated input lengths from zero to the full record size.

**Interview check:** Why can a struct image break across platforms? Padding, alignment and numeric representation are not a protocol contract.

**Exit criterion:** You can prove byte counts, widths and error behavior before any memory access.