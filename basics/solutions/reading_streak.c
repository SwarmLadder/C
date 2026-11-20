#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

Span reading_streak(const uint16_t *v, size_t n, uint16_t target) {
  Span best = {0, 0};
  size_t run = 0;
  for (size_t i = 0; i < n; i++) {
    run = v[i] >= target ? run + 1 : 0;
    if (run > best.len)
      best = (Span){i + 1 - run, run};
  }
  return best;
}
