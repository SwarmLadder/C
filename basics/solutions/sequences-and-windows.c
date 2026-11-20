#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

size_t negatives(const int *v, size_t n) {
  size_t k = 0;
  for (size_t i = 0; i < n; i++)
    k += v[i] < 0;
  return k;
}

size_t rises(const int *v, size_t n) {
  size_t k = 0;
  for (size_t i = 1; i < n; i++)
    k += v[i] > v[i - 1];
  return k;
}

size_t first_index(const int *v, size_t n, int key) {
  for (size_t i = 0; i < n; i++)
    if (v[i] == key)
      return i;
  return n;
}

size_t longest_run(const int *v, size_t n, int key) {
  size_t run = 0, best = 0;
  for (size_t i = 0; i < n; i++) {
    run = v[i] == key ? run + 1 : 0;
    if (run > best)
      best = run;
  }
  return best;
}
