#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

size_t lower_slot(const int *v, size_t n, int key) {
  size_t l = 0, h = n;
  while (l < h) {
    size_t m = l + (h - l) / 2;
    if (v[m] < key)
      l = m + 1;
    else
      h = m;
  }
  return l;
}

size_t upper_slot(const int *v, size_t n, int key) {
  size_t l = 0, h = n;
  while (l < h) {
    size_t m = l + (h - l) / 2;
    if (v[m] <= key)
      l = m + 1;
    else
      h = m;
  }
  return l;
}

void insertion_sort(int *v, size_t n) {
  for (size_t i = 1; i < n; i++) {
    int x = v[i];
    size_t j = i;
    while (j && v[j - 1] > x) {
      v[j] = v[j - 1];
      --j;
    }
    v[j] = x;
  }
}

size_t unique_sorted(int *v, size_t n) {
  size_t w = 0;
  for (size_t i = 0; i < n; i++)
    if (!w || v[i] != v[w - 1])
      v[w++] = v[i];
  return w;
}
