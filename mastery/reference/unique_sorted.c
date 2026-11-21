#include "mastery.h"
bool unique_sorted_i32(int32_t *values, size_t n, size_t *out_count) {
    if (!out_count || (n && !values)) return false;
    for (size_t i = 1; i < n; ++i)
        if (values[i] < values[i - 1]) return false;
    size_t write = 0;
    for (size_t read = 0; read < n; ++read) {
        if (write == 0 || values[read] != values[write - 1]) {
            values[write] = values[read];
            ++write;
        }
    }
    *out_count = write;
    return true;
}
