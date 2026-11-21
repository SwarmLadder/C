#include "mastery.h"
bool decode_frame_header(const uint8_t *data, size_t n, FrameHeader *out) {
    if (!data || !out || n != 9 || data[0] != 0x53 ||
        data[1] != 0x4c || data[2] != 1) return false;
    uint16_t kind = (uint16_t)(((uint16_t)data[3] << 8) | data[4]);
    uint32_t payload = ((uint32_t)data[5] << 24) |
                       ((uint32_t)data[6] << 16) |
                       ((uint32_t)data[7] << 8) | (uint32_t)data[8];
    if (payload > UINT32_C(1048576)) return false;
    FrameHeader result = {data[2], kind, payload};
    *out = result;
    return true;
}
