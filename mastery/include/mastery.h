#ifndef SWARMLADDER_C_MASTERY_H
#define SWARMLADDER_C_MASTERY_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* Preserve *out on all failures, including NULL pointers. */
bool checked_add_i32(int32_t a, int32_t b, int32_t *out);
/* Accept one or more ASCII digits, 0 through UINT32_MAX; no signs or spaces. */
bool parse_u32_strict(const char *text, uint32_t *out);

/* Zero-initialized TextBuffer owns data; len excludes terminating NUL.
 * When cap > 0: data is valid, len < cap and data[len] is NUL.
 * Appended source must not alias buf->data; buffer is unchanged on failure.
 */
typedef struct {
    char *data;
    size_t len, cap;
} TextBuffer;
bool textbuf_append(TextBuffer *buf, const char *source, size_t length);
void textbuf_release(TextBuffer *buf);

/* Count all byte values of stream through EOF. Store fresh counts only on
 * successful read. Caller owns FILE*; never close it here. */
bool count_stream_bytes(FILE *input, uint64_t counts[256]);

typedef struct {
    uint8_t version;
    uint16_t kind;
    uint32_t payload_length;
} FrameHeader;
/* Exactly nine bytes: 'S','L',version=1, kind big-endian 16,
 * payload length big-endian 32, max 1048576. Leave out unchanged on failure.
 */
bool decode_frame_header(const uint8_t *data, size_t length, FrameHeader *out);

typedef struct { size_t from, to; } Edge;
/* Nodes numbered [0,n), 0<=n<=64. Return lexicographically smallest
 * topological ordering (choose smallest available node at each step).
 * Reject invalid edges and cycles without modifying out. */
bool topology_sort(size_t n, const Edge *edges, size_t edge_count, size_t *out);
#endif
