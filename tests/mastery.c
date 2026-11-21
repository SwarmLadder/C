#include "mastery.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK(x) do { if (!(x)) { \
    fprintf(stderr, "%s:%d: failed %s\n", __func__, __LINE__, #x); exit(1); \
} } while (0)

static void check_arithmetic(void) {
    int32_t out = 77;
    CHECK(checked_add_i32(4, 5, &out) && out == 9);
    CHECK(checked_add_i32(INT32_MIN, INT32_MAX, &out) && out == -1);
    CHECK(!checked_add_i32(INT32_MAX, 1, &out) && out == -1);
    CHECK(!checked_add_i32(INT32_MIN, -1, &out) && out == -1);
    CHECK(checked_add_i32(INT32_MIN, 0, &out) && out == INT32_MIN);
    CHECK(checked_add_i32(INT32_MAX, 0, &out) && out == INT32_MAX);
    CHECK(!checked_add_i32(1, 1, NULL));
}
static void check_decimal(void) {
    uint32_t out = 77;
    CHECK(parse_u32_strict("0", &out) && out == 0);
    CHECK(parse_u32_strict("00001", &out) && out == 1);
    CHECK(parse_u32_strict("4294967295", &out) && out == UINT32_MAX);
    CHECK(!parse_u32_strict("4294967296", &out) && out == UINT32_MAX);
    CHECK(!parse_u32_strict("", &out) && out == UINT32_MAX);
    CHECK(!parse_u32_strict("-1", &out) && out == UINT32_MAX);
    CHECK(!parse_u32_strict("+1", &out) && out == UINT32_MAX);
    CHECK(!parse_u32_strict(" 1", &out) && out == UINT32_MAX);
    CHECK(!parse_u32_strict("1x", &out) && out == UINT32_MAX);
    CHECK(!parse_u32_strict("999999999999999", &out) && out == UINT32_MAX);
    CHECK(!parse_u32_strict(NULL, &out) && out == UINT32_MAX);
    CHECK(!parse_u32_strict("1", NULL));
}
static void check_buffer(void) {
    TextBuffer b = {0};
    CHECK(textbuf_append(&b, "", 0));
    CHECK(b.data == NULL && b.len == 0 && b.cap == 0);
    CHECK(textbuf_append(&b, "abc", 3));
    CHECK(b.len == 3 && b.cap >= 4 && strcmp(b.data, "abc") == 0);
    CHECK(textbuf_append(&b, "def", 3));
    CHECK(b.len == 6 && strcmp(b.data, "abcdef") == 0);
    char *old = b.data;
    CHECK(!textbuf_append(&b, NULL, 1) && b.data == old && b.len == 6);
    CHECK(!textbuf_append(&b, "x", SIZE_MAX) && b.data == old && b.len == 6);
    char data[128];
    memset(data, 'z', sizeof data);
    CHECK(textbuf_append(&b, data, sizeof data));
    CHECK(b.len == 134 && b.data[134] == '\0' && b.data[133] == 'z');
    textbuf_release(&b);
    CHECK(b.data == NULL && b.cap == 0 && b.len == 0);
    textbuf_release(&b);
    CHECK(!textbuf_append(NULL, "a", 1));
}
static void check_stream(void) {
    uint64_t counts[256];
    for (size_t i = 0; i < 256; ++i) counts[i] = 88;
    CHECK(!count_stream_bytes(NULL, counts) && counts[0] == 88);
    FILE *in = tmpfile();
    CHECK(in != NULL);
    unsigned char bytes[] = {0, 255, 0, 10, 128, 'A', 'A'};
    CHECK(fwrite(bytes, 1, sizeof bytes, in) == sizeof bytes);
    rewind(in);
    CHECK(count_stream_bytes(in, counts));
    CHECK(counts[0] == 2 && counts[255] == 1 && counts[128] == 1);
    CHECK(counts['A'] == 2 && counts[10] == 1 && counts[1] == 0);
    CHECK(fclose(in) == 0);
    in = tmpfile();
    CHECK(in != NULL);
    CHECK(count_stream_bytes(in, counts));
    for (size_t i = 0; i < 256; ++i) CHECK(counts[i] == 0);
    CHECK(fclose(in) == 0);
}
static void check_frame(void) {
    uint8_t data[9] = {'S', 'L', 1, 0x12, 0x34, 0, 0, 0, 5};
    FrameHeader out = {99, 88, 77};
    CHECK(decode_frame_header(data, 9, &out));
    CHECK(out.version == 1 && out.kind == 0x1234 && out.payload_length == 5);
    CHECK(!decode_frame_header(data, 8, &out) && out.payload_length == 5);
    CHECK(!decode_frame_header(data, 9, NULL));
    CHECK(!decode_frame_header(NULL, 9, &out));
    data[0] = 'X';
    CHECK(!decode_frame_header(data, 9, &out));
    data[0] = 'S'; data[2] = 2;
    CHECK(!decode_frame_header(data, 9, &out));
    data[2] = 1;
    data[5] = 0; data[6] = 16; data[7] = 0; data[8] = 0;
    CHECK(decode_frame_header(data, 9, &out) &&
          out.payload_length == UINT32_C(1048576));
    data[8] = 1;
    CHECK(!decode_frame_header(data, 9, &out) &&
          out.payload_length == UINT32_C(1048576));
}
static void check_topology(void) {
    Edge graph[] = {{0, 2}, {1, 2}, {2, 3}};
    size_t output[] = {9, 9, 9, 9};
    CHECK(topology_sort(4, graph, 3, output));
    CHECK(output[0] == 0 && output[1] == 1 &&
          output[2] == 2 && output[3] == 3);
    Edge cycle[] = {{0, 1}, {1, 0}};
    size_t saved[] = {11, 12};
    CHECK(!topology_sort(2, cycle, 2, saved));
    CHECK(saved[0] == 11 && saved[1] == 12);
    CHECK(!topology_sort(2, graph, 1, saved));
    CHECK(saved[0] == 11 && saved[1] == 12);
    CHECK(topology_sort(0, NULL, 0, NULL));
    CHECK(!topology_sort(65, NULL, 0, output));
    CHECK(!topology_sort(2, NULL, 1, saved));
    CHECK(!topology_sort(2, NULL, 0, NULL));
    CHECK(topology_sort(4, NULL, 0, output));
    CHECK(output[0] == 0 && output[1] == 1 &&
          output[2] == 2 && output[3] == 3);
    Edge duplicate[] = {{0, 2}, {0, 2}, {1, 2}};
    CHECK(topology_sort(3, duplicate, 3, output));
    CHECK(output[0] == 0 && output[1] == 1 && output[2] == 2);
}


static void check_reverse_span(void) {
    uint8_t bytes[] = {0, 255, 2, 3, 4};
    CHECK(reverse_span(NULL, 0));
    CHECK(!reverse_span(NULL, 1));
    CHECK(reverse_span(bytes, 0) && bytes[0] == 0);
    CHECK(reverse_span(bytes, 5));
    CHECK(bytes[0] == 4 && bytes[1] == 3 && bytes[2] == 2 &&
          bytes[3] == 255 && bytes[4] == 0);
    CHECK(reverse_span(bytes, 5));
    CHECK(bytes[0] == 0 && bytes[1] == 255 && bytes[4] == 4);
    CHECK(reverse_span(bytes, 1) && bytes[0] == 0);
    CHECK(reverse_span(bytes, 2) && bytes[0] == 255 && bytes[1] == 0);
}

static void check_parse_hex(void) {
    uint32_t value = 88;
    CHECK(parse_u32_hex("0", &value) && value == 0);
    CHECK(parse_u32_hex("Ff", &value) && value == UINT32_C(255));
    CHECK(parse_u32_hex("0000ABCD", &value) && value == UINT32_C(43981));
    CHECK(parse_u32_hex("ffffffff", &value) && value == UINT32_MAX);
    CHECK(!parse_u32_hex("100000000", &value) && value == UINT32_MAX);
    CHECK(!parse_u32_hex("000000000", &value) && value == UINT32_MAX);
    CHECK(!parse_u32_hex("0xFF", &value) && value == UINT32_MAX);
    CHECK(!parse_u32_hex(" G", &value) && value == UINT32_MAX);
    CHECK(!parse_u32_hex("", &value) && value == UINT32_MAX);
    CHECK(!parse_u32_hex(NULL, &value) && value == UINT32_MAX);
    CHECK(!parse_u32_hex("123", NULL));
    CHECK(parse_u32_hex("deadBEEF", &value) && value == UINT32_C(3735928559));
}

static void check_lower_bound(void) {
    size_t out = 99;
    int32_t values[] = {-7, -1, -1, 0, 3, 3, INT32_MAX};
    CHECK(lower_bound_i32(values, 7, INT32_MIN, &out) && out == 0);
    CHECK(lower_bound_i32(values, 7, -1, &out) && out == 1);
    CHECK(lower_bound_i32(values, 7, 2, &out) && out == 4);
    CHECK(lower_bound_i32(values, 7, 3, &out) && out == 4);
    CHECK(lower_bound_i32(values, 7, INT32_MAX, &out) && out == 6);
    CHECK(lower_bound_i32(NULL, 0, 4, &out) && out == 0);
    CHECK(!lower_bound_i32(NULL, 1, 4, &out) && out == 0);
    CHECK(!lower_bound_i32(values, 7, 3, NULL));
    int32_t equal[] = {9, 9, 9, 9};
    CHECK(lower_bound_i32(equal, 4, 10, &out) && out == 4);
    CHECK(lower_bound_i32(equal, 4, 9, &out) && out == 0);
}

static void check_unique_sorted(void) {
    int32_t items[] = {-4, -4, -1, 0, 0, 0, 5, 5};
    size_t count = 77;
    CHECK(unique_sorted_i32(items, 8, &count) && count == 4);
    CHECK(items[0] == -4 && items[1] == -1 && items[2] == 0 && items[3] == 5);
    CHECK(unique_sorted_i32(items, count, &count) && count == 4);
    CHECK(unique_sorted_i32(NULL, 0, &count) && count == 0);
    CHECK(!unique_sorted_i32(NULL, 1, &count) && count == 0);
    CHECK(!unique_sorted_i32(items, 1, NULL));
    int32_t invalid[] = {0, 5, 3, 9};
    count = 42;
    CHECK(!unique_sorted_i32(invalid, 4, &count));
    CHECK(count == 42 && invalid[0] == 0 && invalid[1] == 5 &&
          invalid[2] == 3 && invalid[3] == 9);
    int32_t single[] = {INT32_MIN};
    CHECK(unique_sorted_i32(single, 1, &count) && count == 1);
}

static void check_ring_queue(void) {
    RingQueue q = {{0}, 0, 0};
    uint32_t out = 777;
    ring_reset(&q);
    CHECK(!ring_pop(&q, &out) && out == 777);
    for (uint32_t i = 0; i < 8; ++i)
        CHECK(ring_push(&q, i * UINT32_C(10)));
    CHECK(q.size == 8 && !ring_push(&q, 90) && q.size == 8);
    for (uint32_t i = 0; i < 3; ++i) {
        CHECK(ring_pop(&q, &out) && out == i * UINT32_C(10));
    }
    CHECK(q.head == 3 && q.size == 5);
    for (uint32_t i = 8; i < 11; ++i)
        CHECK(ring_push(&q, i * UINT32_C(10)));
    for (uint32_t i = 3; i < 11; ++i)
        CHECK(ring_pop(&q, &out) && out == i * UINT32_C(10));
    CHECK(q.size == 0 && !ring_pop(&q, &out) && out == 100);
    CHECK(!ring_pop(NULL, &out));
    CHECK(!ring_pop(&q, NULL));
    CHECK(!ring_push(NULL, 5));
    q.head = 8;
    CHECK(!ring_push(&q, 7) && !ring_pop(&q, &out));
    ring_reset(&q);
    CHECK(q.size == 0 && q.head == 0);
    ring_reset(NULL);
    CHECK(ring_push(&q, UINT32_MAX));
    CHECK(ring_pop(&q, &out) && out == UINT32_MAX);
}

static void check_dag_distances(void) {
    const Edge graph[] = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}};
    const uint32_t weights[] = {4, 2, 1, 7, 3};
    int64_t dist[5] = {77, 77, 77, 77, 77};
    CHECK(dag_distances(5, graph, weights, 5, 0, dist));
    CHECK(dist[0] == 0 && dist[1] == 4 && dist[2] == 2 &&
          dist[3] == 5 && dist[4] == 8);
    CHECK(dag_distances(5, graph, weights, 5, 2, dist));
    CHECK(dist[0] == -1 && dist[1] == -1 && dist[2] == 0 &&
          dist[3] == 7 && dist[4] == 10);
    const Edge cycle[] = {{0, 1}, {1, 0}};
    const uint32_t cycweight[] = {1, 2};
    int64_t unchanged[] = {44, 55};
    CHECK(!dag_distances(2, cycle, cycweight, 2, 0, unchanged));
    CHECK(unchanged[0] == 44 && unchanged[1] == 55);
    CHECK(!dag_distances(0, NULL, NULL, 0, 0, unchanged));
    CHECK(!dag_distances(65, NULL, NULL, 0, 0, unchanged));
    CHECK(!dag_distances(2, NULL, NULL, 0, 2, unchanged));
    CHECK(!dag_distances(2, NULL, NULL, 0, 0, NULL));
    CHECK(!dag_distances(2, graph, NULL, 1, 0, unchanged));
    CHECK(unchanged[0] == 44 && unchanged[1] == 55);
    CHECK(dag_distances(2, NULL, NULL, 0, 0, unchanged));
    CHECK(unchanged[0] == 0 && unchanged[1] == -1);
    const Edge huge[] = {{0, 1}, {1, 2}};
    const uint32_t bigw[] = {UINT32_MAX, UINT32_MAX};
    int64_t bigout[3] = {0};
    CHECK(dag_distances(3, huge, bigw, 2, 0, bigout));
    CHECK(bigout[2] == INT64_C(8589934590));
    const Edge dup[] = {{0, 1}, {0, 1}, {1, 2}};
    const uint32_t dupw[] = {10, 1, 2};
    CHECK(dag_distances(3, dup, dupw, 3, 0, bigout));
    CHECK(bigout[1] == 1 && bigout[2] == 3);
    const Edge self[] = {{0, 0}};
    const uint32_t selfw[] = {0};
    int64_t flag = 9;
    CHECK(!dag_distances(1, self, selfw, 1, 0, &flag) && flag == 9);
}

int main(int argc, char **argv) {
    struct Task { const char *name; const char *level; void (*test)(void); };
    const struct Task tasks[] = {
        {"checked_add", "basics", check_arithmetic},
        {"parse_decimal", "basics", check_decimal},
        {"text_buffer", "intermediate", check_buffer},
        {"byte_histogram", "intermediate", check_stream},
        {"frame_header", "advanced", check_frame},
        {"topological", "advanced", check_topology},
        {"reverse_span", "basics", check_reverse_span},
        {"parse_hex", "basics", check_parse_hex},
        {"lower_bound", "intermediate", check_lower_bound},
        {"unique_sorted", "intermediate", check_unique_sorted},
        {"ring_queue", "advanced", check_ring_queue},
        {"dag_distances", "advanced", check_dag_distances}
    };
    size_t n = 0;
    for (size_t i = 0; i < sizeof tasks / sizeof tasks[0]; ++i) {
        if (argc > 1 && argv[1][0] && strcmp(argv[1], tasks[i].name)) continue;
        if (argc > 2 && argv[2][0] && strcmp(argv[2], tasks[i].level)) continue;
        tasks[i].test();
        ++n;
    }
    if (!n) { fputs("Unknown mastery task\n", stderr); return 2; }
    printf("%zu mastery labs passed\n", n);
    return 0;
}
