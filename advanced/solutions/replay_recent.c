#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

size_t replay_recent(const int *v, size_t n, int *out) {
  int ring[8];
  size_t head = 0, len = 0;
  for (size_t i = 0; i < n; i++) {
    ring[(head + len) % 8] = v[i];
    if (len < 8)
      ++len;
    else
      head = (head + 1) % 8;
  }
  for (size_t i = 0; i < len; i++)
    out[i] = ring[(head + i) % 8];
  return len;
}
