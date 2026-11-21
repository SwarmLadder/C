#include "mastery.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
bool textbuf_append(TextBuffer *b, const char *src, size_t n) {
    if (b == NULL || (src == NULL && n != 0)) return false;
    if (b->len > b->cap ||
        (b->cap == 0 && (b->data != NULL || b->len != 0)) ||
        (b->cap > 0 && (b->data == NULL || b->len >= b->cap))) return false;
    if (n == 0) return true;
    if (b->len == SIZE_MAX || n > SIZE_MAX - b->len - 1) return false;
    size_t required = b->len + n + 1;
    if (required > b->cap) {
        size_t cap = b->cap != 0 ? b->cap : 16;
        while (cap < required) {
            if (cap > SIZE_MAX / 2) { cap = required; break; }
            cap *= 2;
        }
        char *next = realloc(b->data, cap);
        if (!next) return false;
        b->data = next;
        b->cap = cap;
    }
    memcpy(b->data + b->len, src, n);
    b->len += n;
    b->data[b->len] = '\0';
    return true;
}
void textbuf_release(TextBuffer *b) {
    if (!b) return;
    free(b->data);
    b->data = NULL;
    b->len = b->cap = 0;
}
