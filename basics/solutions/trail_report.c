#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

Trail trail_report(const int16_t *v, size_t n) {
  Trail t = {0, 0};
  for (size_t i = 1; i < n; i++) {
    long d = (long)v[i] - v[i - 1];
    if (d > 0)
      t.ascent += (uint64_t)d;
    if (v[i] > v[t.peak])
      t.peak = i;
  }
  return t;
}
