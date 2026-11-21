#include "mastery.h"
#include <stdint.h>
#include <string.h>
bool count_stream_bytes(FILE *input, uint64_t counts[256]) {
    if (!input || !counts) return false;
    uint64_t staged[256] = {0};
    unsigned char buffer[4096];
    for (;;) {
        size_t n = fread(buffer, 1, sizeof buffer, input);
        for (size_t i = 0; i < n; ++i) {
            if (staged[buffer[i]] == UINT64_MAX) return false;
            ++staged[buffer[i]];
        }
        if (n != sizeof buffer) {
            if (ferror(input)) return false;
            break;
        }
    }
    memcpy(counts, staged, sizeof staged);
    return true;
}
