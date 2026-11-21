#include "mastery.h"
bool parse_u32_hex(const char *text, uint32_t *out) {
    if (!text || !out || text[0] == '\0') return false;
    uint32_t value = 0;
    size_t count = 0;
    for (size_t i = 0; text[i] != '\0'; ++i) {
        unsigned digit;
        char c = text[i];
        if (c >= '0' && c <= '9') digit = (unsigned)(c - '0');
        else if (c >= 'a' && c <= 'f') digit = (unsigned)(c - 'a' + 10);
        else if (c >= 'A' && c <= 'F') digit = (unsigned)(c - 'A' + 10);
        else return false;
        if (count == 8) return false;
        value = (value << 4) | (uint32_t)digit;
        ++count;
    }
    *out = value;
    return true;
}
