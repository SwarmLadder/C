#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int sign_of(int x) { return (x > 0) - (x < 0); }

bool leap_year(unsigned y) {
  return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
}

unsigned fare(unsigned age) {
  if (age < 6)
    return 0;
  if (age < 18)
    return 2;
  return age >= 65 ? 3 : 5;
}

int middle(int a, int b, int c) {
  if (a > b) {
    int t = a;
    a = b;
    b = t;
  }
  if (b > c)
    b = c;
  return a > b ? a : b;
}
