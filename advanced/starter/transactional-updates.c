#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool debit(unsigned *balance, unsigned amount) {
  (void)balance;
  (void)amount;
  fputs("Implement debit\n", stderr);
  exit(EXIT_FAILURE);
}

bool credit(unsigned *balance, unsigned amount) {
  (void)balance;
  (void)amount;
  fputs("Implement credit\n", stderr);
  exit(EXIT_FAILURE);
}

bool move_funds(unsigned *a, size_t n, Move m) {
  (void)a;
  (void)n;
  (void)m;
  fputs("Implement move_funds\n", stderr);
  exit(EXIT_FAILURE);
}

bool settle_four(unsigned *accounts, const Move *moves, size_t n) {
  (void)accounts;
  (void)moves;
  (void)n;
  fputs("Implement settle_four\n", stderr);
  exit(EXIT_FAILURE);
}
