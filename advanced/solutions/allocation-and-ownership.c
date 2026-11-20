#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int *clone_values(const int *v, size_t n) {
  if (!n || n > SIZE_MAX / sizeof *v)
    return NULL;
  int *p = malloc(n * sizeof *p);
  if (p)
    memcpy(p, v, n * sizeof *p);
  return p;
}

bool reserve_values(Vector *v, size_t need) {
  if (need <= v->cap)
    return true;
  if (need > SIZE_MAX / sizeof *v->data)
    return false;
  int *p = realloc(v->data, need * sizeof *p);
  if (!p)
    return false;
  v->data = p;
  v->cap = need;
  return true;
}

bool push_value(Vector *v, int x) {
  if (v->len == v->cap) {
    size_t max = SIZE_MAX / sizeof *v->data;
    if (v->cap == max)
      return false;
    size_t next = v->cap == 0 ? 1 : v->cap > max / 2 ? max : v->cap * 2;
    int *p = realloc(v->data, next * sizeof *p);
    if (!p)
      return false;
    v->data = p;
    v->cap = next;
  }
  v->data[v->len++] = x;
  return true;
}

void release_values(Vector *v) {
  free(v->data);
  *v = (Vector){0};
}
