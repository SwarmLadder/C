#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

size_t count_if(const int *v, size_t n, Predicate test, void *ctx) {
  (void)v;
  (void)n;
  (void)test;
  (void)ctx;
  fputs("Implement count_if\n", stderr);
  exit(EXIT_FAILURE);
}

size_t first_if(const int *v, size_t n, Predicate test, void *ctx) {
  (void)v;
  (void)n;
  (void)test;
  (void)ctx;
  fputs("Implement first_if\n", stderr);
  exit(EXIT_FAILURE);
}

void apply_each(int *v, size_t n, Transform f) {
  (void)v;
  (void)n;
  (void)f;
  fputs("Implement apply_each\n", stderr);
  exit(EXIT_FAILURE);
}

size_t take_while(const int *v, size_t n, Predicate f, void *ctx) {
  (void)v;
  (void)n;
  (void)f;
  (void)ctx;
  fputs("Implement take_while\n", stderr);
  exit(EXIT_FAILURE);
}
