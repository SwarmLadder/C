#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

uint16_t read_be16(const uint8_t *p) {
  return (uint16_t)((uint32_t)p[0] * 256 + p[1]);
}

void write_le32(uint8_t *p, uint32_t x) {
  for (unsigned i = 0; i < 4; i++) {
    p[i] = (uint8_t)x;
    x >>= 8;
  }
}

bool next_frame(Slice *input, Slice *payload) {
  if (input->len < 2)
    return false;
  const uint8_t *p = input->data;
  size_t n = (size_t)p[0] * 256 + p[1];
  if (n > input->len - 2)
    return false;
  *payload = (Slice){p + 2, n};
  input->data = p + 2 + n;
  input->len -= 2 + n;
  return true;
}

uint8_t check_byte(const uint8_t *p, size_t n) {
  uint8_t c = 0;
  for (size_t i = 0; i < n; i++)
    c = (uint8_t)(c - p[i]);
  return c;
}
