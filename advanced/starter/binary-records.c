#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

uint16_t read_be16(const uint8_t *p) {
  (void)p;
  fputs("Implement read_be16\n", stderr);
  exit(EXIT_FAILURE);
}

void write_le32(uint8_t *p, uint32_t x) {
  (void)p;
  (void)x;
  fputs("Implement write_le32\n", stderr);
  exit(EXIT_FAILURE);
}

bool next_frame(Slice *input, Slice *payload) {
  (void)input;
  (void)payload;
  fputs("Implement next_frame\n", stderr);
  exit(EXIT_FAILURE);
}

uint8_t check_byte(const uint8_t *p, size_t n) {
  (void)p;
  (void)n;
  fputs("Implement check_byte\n", stderr);
  exit(EXIT_FAILURE);
}
