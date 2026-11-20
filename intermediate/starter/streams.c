#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int first_byte(FILE *in) {
  (void)in;
  fputs("Implement first_byte\n", stderr);
  exit(EXIT_FAILURE);
}

size_t newlines(FILE *in) {
  (void)in;
  fputs("Implement newlines\n", stderr);
  exit(EXIT_FAILURE);
}

bool emit_line(FILE *out, const char *s) {
  (void)out;
  (void)s;
  fputs("Implement emit_line\n", stderr);
  exit(EXIT_FAILURE);
}

bool copy_stream(FILE *in, FILE *out) {
  (void)in;
  (void)out;
  fputs("Implement copy_stream\n", stderr);
  exit(EXIT_FAILURE);
}
