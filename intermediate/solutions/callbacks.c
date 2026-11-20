#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

size_t count_if(const int *v, size_t n, Predicate test, void *ctx) {
  size_t k = 0;
  for (size_t i = 0; i < n; i++)
    k += test(v[i], ctx);
  return k;
}

size_t first_if(const int *v, size_t n, Predicate test, void *ctx) {
  for (size_t i = 0; i < n; i++)
    if (test(v[i], ctx))
      return i;
  return n;
}

void apply_each(int *v, size_t n, Transform f) {
  for (size_t i = 0; i < n; i++)
    v[i] = f(v[i]);
}

size_t take_while(const int *v, size_t n, Predicate f, void *ctx) {
  size_t i = 0;
  while (i < n && f(v[i], ctx))
    ++i;
  return i;
}
