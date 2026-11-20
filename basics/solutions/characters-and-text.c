#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool ascii_digit(char c) { return c >= 48 && c <= 57; }

char ascii_lower(char c) { return c >= 65 && c <= 90 ? (char)(c + 32) : c; }

size_t byte_length(const char *s) {
  size_t n = 0;
  while (s[n])
    ++n;
  return n;
}

size_t words(const char *s) {
  size_t n = 0;
  bool in = false;
  for (; *s; ++s) {
    bool text = *s != 32 && *s != 9;
    if (text && !in)
      ++n;
    in = text;
  }
  return n;
}
