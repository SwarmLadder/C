#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool decimal_byte(const char *s, uint8_t *out) {
  if (!*s)
    return false;
  unsigned x = 0;
  for (; *s; s++) {
    if (*s < 48 || *s > 57)
      return false;
    x = x * 10 + (unsigned)(*s - 48);
    if (x > 255)
      return false;
  }
  *out = (uint8_t)x;
  return true;
}

int hex_digit(char c) {
  if (c >= 48 && c <= 57)
    return c - 48;
  if (c >= 65 && c <= 70)
    return c - 65 + 10;
  if (c >= 97 && c <= 102)
    return c - 97 + 10;
  return -1;
}

size_t columns(const char *s) {
  size_t n = 1;
  for (; *s; s++)
    if (*s == 9)
      ++n;
  return n;
}

bool key_span(const char *s, size_t *length) {
  const char *p = strchr(s, 61);
  if (!p || p == s)
    return false;
  *length = (size_t)(p - s);
  return true;
}
