#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool copy_text(char *dst, size_t cap, const char *src) {
  size_t n = strlen(src);
  if (n >= cap)
    return false;
  memcpy(dst, src, n + 1);
  return true;
}

void reverse_ints(int *v, size_t n) {
  for (size_t i = 0; i < n / 2; i++) {
    int t = v[i];
    v[i] = v[n - 1 - i];
    v[n - 1 - i] = t;
  }
}

size_t compact(int *v, size_t n, int skip) {
  size_t w = 0;
  for (size_t i = 0; i < n; i++)
    if (v[i] != skip)
      v[w++] = v[i];
  return w;
}

bool erase_at(int *v, size_t n, size_t i) {
  if (i >= n)
    return false;
  memmove(v + i, v + i + 1, (n - i - 1) * sizeof *v);
  return true;
}
