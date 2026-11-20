#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool transcript(FILE *in, FILE *out) {
  size_t line = 0;
  bool start = true;
  int c;
  while ((c = fgetc(in)) != EOF) {
    if (start && fprintf(out, "%zu ", ++line) < 0)
      return false;
    if (fputc(c, out) == EOF)
      return false;
    start = c == 10;
  }
  return !ferror(in);
}
