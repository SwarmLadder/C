#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool grade_bins(const unsigned *v, size_t n, size_t *bins) {
  size_t b[5] = {0};
  for (size_t i = 0; i < n; i++) {
    if (v[i] > 100)
      return false;
    size_t j = v[i] < 60 ? 0 : v[i] >= 90 ? 4 : v[i] / 10 - 5;
    ++b[j];
  }
  memcpy(bins, b, sizeof b);
  return true;
}
