#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool room_usage(const Slot *v, size_t n, unsigned *used) {
  bool busy[1440] = {false};
  for (size_t i = 0; i < n; i++) {
    if (v[i].begin >= v[i].end || v[i].end > 1440)
      return false;
    for (unsigned j = v[i].begin; j < v[i].end; j++)
      busy[j] = true;
  }
  unsigned k = 0;
  for (size_t j = 0; j < 1440; j++)
    k += busy[j];
  *used = k;
  return true;
}
