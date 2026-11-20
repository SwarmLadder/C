#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int first_byte(FILE *in) { return fgetc(in); }

size_t newlines(FILE *in) {
  size_t n = 0;
  int c;
  while ((c = fgetc(in)) != EOF)
    n += c == 10;
  return n;
}

bool emit_line(FILE *out, const char *s) {
  return fputs(s, out) != EOF && fputc(10, out) != EOF;
}

bool copy_stream(FILE *in, FILE *out) {
  int c;
  while ((c = fgetc(in)) != EOF) {
    if (fputc(c, out) == EOF)
      return false;
  }
  return !ferror(in);
}
