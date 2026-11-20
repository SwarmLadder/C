#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

long point_total(Point p) { return (long)p.x + p.y; }

bool on_axis(Point p) { return p.x == 0 || p.y == 0; }

size_t best_point(const Point *p, size_t n) {
  if (!n)
    return n;
  size_t best = 0;
  for (size_t i = 1; i < n; i++)
    if ((long)p[i].x + p[i].y > (long)p[best].x + p[best].y)
      best = i;
  return best;
}

size_t enclosed(const Point *p, size_t n, int16_t limit) {
  if (limit < 0)
    return 0;
  size_t k = 0;
  for (size_t i = 0; i < n; i++)
    k += p[i].x >= -limit && p[i].x <= limit && p[i].y >= -limit &&
         p[i].y <= limit;
  return k;
}
