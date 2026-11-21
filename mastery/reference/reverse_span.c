#include "mastery.h"
bool reverse_span(uint8_t *data, size_t n) {
    if (!data && n) return false;
    for (size_t left = 0; left < n / 2; ++left) {
        size_t right = n - 1 - left;
        uint8_t saved = data[left];
        data[left] = data[right];
        data[right] = saved;
    }
    return true;
}
