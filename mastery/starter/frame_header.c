#include "mastery.h"
bool decode_frame_header(const uint8_t *data, size_t length, FrameHeader *out) {
    (void)data; (void)length; (void)out;
    /* TODO: nine-byte validated big-endian header, failure preservation. */
    return false;
}
