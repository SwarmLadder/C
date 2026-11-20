#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

unsigned whole_minutes(unsigned s) { return s / 60; }

unsigned clock_seconds(unsigned s) { return s % 60; }

unsigned billed_hours(unsigned m) { return m / 60 + (m % 60 != 0); }

uint32_t tile_area(uint16_t a, uint16_t b) { return (uint32_t)a * b; }
