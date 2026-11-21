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

/* Enrichment labs B3/B4: length-bounded byte mutation and strict hex.
 * reverse_span: length zero accepts NULL. Positive length requires length
 * accessible uint8_t elements; failure does not modify bytes.
 * parse_u32_hex: accepts 1..8 ASCII hexadecimal digits, no prefix/sign/space;
 * leaves *out unchanged if invalid or NULL.
 */
bool reverse_span(uint8_t *data, size_t length);
bool parse_u32_hex(const char *text, uint32_t *out);

/* Enrichment I3/I4: input must be sorted nondecreasing.
 * lower_bound: n=0 accepts NULL values; always requires non-NULL out.
 * unique_sorted: detects unsorted input before modification and preserves
 * values and *out_count on failure; compacts unique values in-place on success.
 */
bool lower_bound_i32(const int32_t *values, size_t n, int32_t key,
                     size_t *out_index);
bool unique_sorted_i32(int32_t *values, size_t n, size_t *out_count);

/* Enrichment A3: fixed-capacity FIFO of exactly eight unsigned values.
 * Use ring_reset on a live RingQueue before operations. All failures keep
 * the queue and output unchanged. ring_pop returns false when empty.
 */
typedef struct {
    uint32_t values[8];
    size_t head;
    size_t size;
} RingQueue;
void ring_reset(RingQueue *queue);
bool ring_push(RingQueue *queue, uint32_t value);
bool ring_pop(RingQueue *queue, uint32_t *out);

/* Enrichment A4: minimum weighted path lengths in a directed acyclic graph.
 * 1<=n<=64, edges are in [0,n), weights are nonnegative uint32_t.
 * source<n. Unreachable nodes report -1, source reports 0.
 * Cycle/invalid args fail without changing the n-element output.
 * Path sums fit int64_t because paths in a DAG visit <=64 vertices.
 */
bool dag_distances(size_t n, const Edge *edges, const uint32_t *weights,
                   size_t edge_count, size_t source, int64_t *out);

#endif
