#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool copy_text(char *dst, size_t cap, const char *src) {
  (void)dst;
  (void)cap;
  (void)src;
  fputs("Implement copy_text\n", stderr);
  exit(EXIT_FAILURE);
}

void reverse_ints(int *v, size_t n) {
  (void)v;
  (void)n;
  fputs("Implement reverse_ints\n", stderr);
  exit(EXIT_FAILURE);
}

size_t compact(int *v, size_t n, int skip) {
  (void)v;
  (void)n;
  (void)skip;
  fputs("Implement compact\n", stderr);
  exit(EXIT_FAILURE);
}

bool erase_at(int *v, size_t n, size_t i) {
  (void)v;
  (void)n;
  (void)i;
  fputs("Implement erase_at\n", stderr);
  exit(EXIT_FAILURE);
}
