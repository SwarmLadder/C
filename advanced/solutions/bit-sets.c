#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool bit_member(uint32_t set, unsigned i) {
  return i < 32 && (set & (UINT32_C(1) << i)) != 0;
}

bool bit_toggle(uint32_t *set, unsigned i) {
  if (i >= 32)
    return false;
  *set ^= UINT32_C(1) << i;
  return true;
}

unsigned population(uint32_t set) {
  unsigned n = 0;
  while (set) {
    set &= set - 1;
    ++n;
  }
  return n;
}

uint32_t rotate_left(uint32_t x, unsigned n) {
  n %= 32;
  if (!n)
    return x;
  return (uint32_t)(((uint64_t)x << n) | (x >> (32 - n)));
}
