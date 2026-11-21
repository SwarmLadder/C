#include "mastery.h"
#include <stdint.h>
bool checked_add_i32(int32_t a, int32_t b, int32_t *out) {
    if (out == NULL) return false;
    if (b > 0 && a > INT32_MAX - b) return false;
    if (b < 0 && a < INT32_MIN - b) return false;
    *out = a + b;
    return true;
}
