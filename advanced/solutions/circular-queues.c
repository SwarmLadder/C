#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool ring_put(Ring *r, int x) {
  if (r->len == 8)
    return false;
  r->data[(r->head + r->len) % 8] = x;
  ++r->len;
  return true;
}

bool ring_get(Ring *r, int *out) {
  if (!r->len)
    return false;
  *out = r->data[r->head];
  r->head = (r->head + 1) % 8;
  --r->len;
  return true;
}

bool ring_at(const Ring *r, size_t i, int *out) {
  if (i >= r->len)
    return false;
  *out = r->data[(r->head + i) % 8];
  return true;
}

size_t ring_drop(Ring *r, size_t n) {
  if (n > r->len)
    n = r->len;
  r->head = (r->head + n) % 8;
  r->len -= n;
  return n;
}
