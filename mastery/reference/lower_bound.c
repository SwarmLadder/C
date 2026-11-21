#include "mastery.h"
bool lower_bound_i32(const int32_t *values, size_t n, int32_t key,
                     size_t *out_index) {
    if (!out_index || (n && !values)) return false;
    size_t low = 0, high = n;
    while (low < high) {
        size_t middle = low + (high - low) / 2;
        if (values[middle] < key) low = middle + 1;
        else high = middle;
    }
    *out_index = low;
    return true;
}
