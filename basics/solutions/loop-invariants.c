#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

unsigned digit_sum(unsigned n) {
  unsigned s = 0;
  while (n) {
    s += n % 10;
    n /= 10;
  }
  return s;
}

unsigned digit_count(unsigned n) {
  unsigned k = 1;
  while (n >= 10) {
    n /= 10;
    ++k;
  }
  return k;
}

unsigned gcd_of(unsigned a, unsigned b) {
  while (b) {
    unsigned r = a % b;
    a = b;
    b = r;
  }
  return a;
}

bool is_prime(unsigned n) {
  if (n < 2)
    return false;
  for (unsigned i = 2; i <= n / i; i++) {
    if (n % i == 0)
      return false;
  }
  return true;
}
