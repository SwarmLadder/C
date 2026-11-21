#include "mastery.h"
bool count_stream_bytes(FILE *input, uint64_t counts[256]) {
    (void)input; (void)counts;
    /* TODO: fread bytes in blocks; publish counts only at EOF without error. */
    return false;
}
