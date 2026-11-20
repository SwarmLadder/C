#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int *clone_values(const int *v, size_t n) {
  (void)v;
  (void)n;
  fputs("Implement clone_values\n", stderr);
  exit(EXIT_FAILURE);
}

bool reserve_values(Vector *v, size_t need) {
  (void)v;
  (void)need;
  fputs("Implement reserve_values\n", stderr);
  exit(EXIT_FAILURE);
}

bool push_value(Vector *v, int x) {
  (void)v;
  (void)x;
  fputs("Implement push_value\n", stderr);
  exit(EXIT_FAILURE);
}

void release_values(Vector *v) {
  (void)v;
  fputs("Implement release_values\n", stderr);
  exit(EXIT_FAILURE);
}
