#include "mastery.h"
void ring_reset(RingQueue *queue) {
    if (!queue) return;
    queue->head = 0;
    queue->size = 0;
}
bool ring_push(RingQueue *queue, uint32_t value) {
    if (!queue || queue->size >= 8 || queue->head >= 8) return false;
    const size_t index = (queue->head + queue->size) % 8;
    queue->values[index] = value;
    ++queue->size;
    return true;
}
bool ring_pop(RingQueue *queue, uint32_t *out) {
    if (!queue || !out || queue->size == 0 || queue->size > 8 ||
        queue->head >= 8) return false;
    *out = queue->values[queue->head];
    queue->head = (queue->head + 1) % 8;
    --queue->size;
    return true;
}
