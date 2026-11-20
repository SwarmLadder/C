#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool inspect_capture(Slice input, size_t *count) {
  size_t k = 0;
  while (input.len) {
    if (input.len < 2)
      return false;
    size_t n = (size_t)input.data[0] * 256 + input.data[1];
    if (n > input.len - 2)
      return false;
    input.data += 2 + n;
    input.len -= 2 + n;
    ++k;
  }
  *count = k;
  return true;
}
