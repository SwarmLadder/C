#include "mastery.h"
bool textbuf_append(TextBuffer *buf, const char *source, size_t length) {
    (void)buf; (void)source; (void)length;
    /* TODO: checked growth, realloc through temporary, NUL termination. */
    return false;
}
void textbuf_release(TextBuffer *buf) {
    (void)buf;
    /* TODO: free owned storage, reset fields. */
}
