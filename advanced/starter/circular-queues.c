#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool ring_put(Ring *r, int x) {
  (void)r;
  (void)x;
  fputs("Implement ring_put\n", stderr);
  exit(EXIT_FAILURE);
}

bool ring_get(Ring *r, int *out) {
  (void)r;
  (void)out;
  fputs("Implement ring_get\n", stderr);
  exit(EXIT_FAILURE);
}

bool ring_at(const Ring *r, size_t i, int *out) {
  (void)r;
  (void)i;
  (void)out;
  fputs("Implement ring_at\n", stderr);
  exit(EXIT_FAILURE);
}

size_t ring_drop(Ring *r, size_t n) {
  (void)r;
  (void)n;
  fputs("Implement ring_drop\n", stderr);
  exit(EXIT_FAILURE);
}
