# Mastery lab I1 — Resizable, owned text buffer

**Difficulty:** intermediate / memory safety. **Targets:** textbuf_append and textbuf_release. **Suggested time:** 90–150 minutes.

## Representation and invariants

A TextBuffer contains an owning char pointer, logical length and allocated capacity. Initially all fields are zero. When capacity is nonzero, data points to owned writable memory, length is strictly smaller than capacity, and data[length] is the terminating zero byte. The function appends an explicit number of bytes; the source is **not permitted to alias the destination allocation**.

On failure (bad arguments, overflow, allocation failure, invalid buffer state) the buffer's pointer, length, capacity and previous contents must remain unchanged. This is a strong failure guarantee.

## Worked capacity reasoning

To append n bytes to an existing length L, storage needs L+n+1 bytes including a terminator. Prove the sum fits size_t before computing it. If capacity is insufficient, start at an initial nonzero capacity and double geometrically, with overflow handling. A temporary realloc pointer preserves the previous allocation if growth fails.

After successful allocation, copy exactly n source bytes to data+L, set length=L+n, then terminate. A zero-length append can succeed without allocating. Release frees the owned allocation and zeroes all fields; repeated release is intentionally supported.

## Failure cases to test

- Starting from an all-zero buffer; append "abc", then "def".
- Append 128 bytes to force growth while retaining the original prefix.
- Append zero bytes and observe that state remains valid.
- Reject NULL source with positive length.
- Reject a length of SIZE_MAX before copying.
- Call release twice and confirm no pointer is used afterward.

Implement mastery/starter/text_buffer.c, then run:

~~~sh
make mastery-check TASK=text_buffer
~~~

## Deep variations

1. Add reserve and clear functions and prove that clear does not need to release capacity.
2. Add a function that appends from within the current buffer. Explain why a naive memcpy after realloc is unsafe when src aliases the old allocation; solve with an offset or temporary copy.
3. Build a small line reader on top of TextBuffer and specify its maximum accepted line length.

**Proof prompt:** Show that len<cap and data[len]=='\0' hold after every successful nonempty append; show why every failure preserves the prior state.

**Interview follow-up:** Why is doubling capacity amortized efficient? The total copied bytes over n appends are bounded by a geometric sum O(n).