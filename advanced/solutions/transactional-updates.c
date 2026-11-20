#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool debit(unsigned *balance, unsigned amount) {
  if (amount > *balance)
    return false;
  *balance -= amount;
  return true;
}

bool credit(unsigned *balance, unsigned amount) {
  if (amount > UINT_MAX - *balance)
    return false;
  *balance += amount;
  return true;
}

bool move_funds(unsigned *a, size_t n, Move m) {
  if (m.from >= n || m.to >= n || m.from == m.to || a[m.from] < m.amount ||
      m.amount > UINT_MAX - a[m.to])
    return false;
  a[m.from] -= m.amount;
  a[m.to] += m.amount;
  return true;
}

bool settle_four(unsigned *accounts, const Move *moves, size_t n) {
  unsigned a[4];
  memcpy(a, accounts, sizeof a);
  for (size_t i = 0; i < n; i++) {
    Move m = moves[i];
    if (m.from >= 4 || m.to >= 4 || m.from == m.to || a[m.from] < m.amount ||
        m.amount > UINT_MAX - a[m.to])
      return false;
    a[m.from] -= m.amount;
    a[m.to] += m.amount;
  }
  memcpy(accounts, a, sizeof a);
  return true;
}
