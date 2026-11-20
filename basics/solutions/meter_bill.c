#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

uint64_t meter_bill(const uint16_t *minutes, size_t n) {
  uint64_t total = 0;
  for (size_t i = 0; i < n; i++)
    if (minutes[i] > 5)
      total += UINT64_C(3) * (((uint32_t)minutes[i] - 5 + 14) / 15);
  return total;
}
