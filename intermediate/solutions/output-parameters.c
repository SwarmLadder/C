#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool safe_add(unsigned a, unsigned b, unsigned *out) {
  if (b > UINT_MAX - a)
    return false;
  *out = a + b;
  return true;
}

bool safe_mul(unsigned a, unsigned b, unsigned *out) {
  if (a && b > UINT_MAX / a)
    return false;
  *out = a * b;
  return true;
}

bool range_of(const int *v, size_t n, int *lo, int *hi) {
  if (!n)
    return false;
  int a = v[0], b = a;
  for (size_t i = 1; i < n; i++) {
    if (v[i] < a)
      a = v[i];
    if (v[i] > b)
      b = v[i];
  }
  *lo = a;
  *hi = b;
  return true;
}

bool div_parts(unsigned n, unsigned d, unsigned *q, unsigned *r) {
  if (!d)
    return false;
  *q = n / d;
  *r = n % d;
  return true;
}
