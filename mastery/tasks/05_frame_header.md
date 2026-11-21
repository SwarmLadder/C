# Mastery lab A1 — Portable binary frame decoder

**Difficulty:** advanced / protocol security. **Target:** decode_frame_header. **Suggested time:** 90–140 minutes.

## Wire protocol

Exactly nine bytes describe a frame:

| Offset | Width | Meaning |
| --- | --- | --- |
| 0–1 | 2 bytes | Magic characters S and L |
| 2 | 1 byte | Version, must equal 1 |
| 3–4 | 2 bytes | Unsigned kind, network big-endian |
| 5–8 | 4 bytes | Unsigned payload length, network big-endian |

The payload length must not exceed 1,048,576. No payload is part of this task. Reject NULL pointers, incorrect byte counts, invalid magic/version, or excessive payload lengths. On failure leave the output FrameHeader completely unchanged.

## Portable decoding

Do not cast the input bytes to FrameHeader*: struct padding, alignment, integer byte order and effective types are not a portable wire contract. Decode with uint8_t indexing and unsigned shifts. Cast input bytes to sufficiently wide unsigned integer types **before** shifting by 24 or 16 bits.

Validate the array length before reading byte 8, even if the input advertises a small payload. Build a complete local FrameHeader value, then assign it to the caller only when all checks succeed.

## Test-driven examples

- S L, version 1, kind 0x1234, length 5 must decode correctly.
- A truncated 8-byte frame must be rejected without altering output.
- Changing S to X or version to 2 must be rejected.
- Exactly 1,048,576 payload bytes is the maximum accepted declared size.
- Declared length 1,048,577 must fail while retaining the previous result.

Run:

~~~sh
make mastery-check TASK=frame_header
~~~

## Extensions

Write the inverse encoder and demonstrate decode(encode(x))=x for valid headers. Add a checksum field and decide what the checksum covers. Simulate truncation at every byte position and test under AddressSanitizer. Add version 2 without silently changing version 1 layout.

**Proof prompt:** Show which precondition establishes that each accessed byte offset exists.

**Interview follow-up:** Why is memcpy into a struct not enough for cross-platform wire decoding? Its byte representation still depends on layout and endianness.