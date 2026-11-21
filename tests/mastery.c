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

int main(int argc, char **argv) {
    struct Task { const char *name; const char *level; void (*test)(void); };
    const struct Task tasks[] = {
        {"checked_add", "basics", check_arithmetic},
        {"parse_decimal", "basics", check_decimal},
        {"text_buffer", "intermediate", check_buffer},
        {"byte_histogram", "intermediate", check_stream},
        {"frame_header", "advanced", check_frame},
        {"topological", "advanced", check_topology}
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
