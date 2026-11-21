#include "mastery.h"
#include <stdint.h>
bool parse_u32_strict(const char *s, uint32_t *out) {
    if (!s || !out || !*s) return false;
    uint32_t result = 0;
    for (size_t i = 0; s[i] != '\0'; ++i) {
        if (s[i] < '0' || s[i] > '9') return false;
        uint32_t digit = (uint32_t)(s[i] - '0');
        if (result > (UINT32_MAX - digit) / UINT32_C(10)) return false;
        result = result * UINT32_C(10) + digit;
    }
    *out = result;
    return true;
}
