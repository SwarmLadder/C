#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool audit_stock(unsigned *bins, const Move *v, size_t n, size_t *bad) {
  unsigned b[4];
  memcpy(b, bins, sizeof b);
  for (size_t i = 0; i < n; i++) {
    Move m = v[i];
    if (m.from >= 4 || m.to >= 4 || m.from == m.to || m.amount > b[m.from] ||
        m.amount > UINT_MAX - b[m.to]) {
      *bad = i;
      return false;
    }
    b[m.from] -= m.amount;
    b[m.to] += m.amount;
  }
  memcpy(bins, b, sizeof b);
  *bad = n;
  return true;
}
