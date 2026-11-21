#include <stddef.h>

/* Stable in-place compaction using a read and a write position. */
void move_zeros(int *values, size_t n) {
    if (n == 0) return;
    size_t write = 0;
    for (size_t read = 0; read < n; ++read) {
        if (values[read] != 0) values[write++] = values[read];
    }
    while (write < n) values[write++] = 0;
}
