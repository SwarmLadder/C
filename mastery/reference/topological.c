#include "mastery.h"
#include <string.h>
#include <stdint.h>
bool topology_sort(size_t n, const Edge *edges, size_t m, size_t *out) {
    if (n > 64 || (n > 0 && !out) || (m > 0 && !edges)) return false;
    size_t degree[64] = {0}, staged[64];
    bool picked[64] = {false};
    for (size_t i = 0; i < m; ++i) {
        if (edges[i].from >= n || edges[i].to >= n ||
            degree[edges[i].to] == SIZE_MAX) return false;
        ++degree[edges[i].to];
    }
    for (size_t step = 0; step < n; ++step) {
        size_t next = n;
        for (size_t v = 0; v < n; ++v) {
            if (!picked[v] && degree[v] == 0) { next = v; break; }
        }
        if (next == n) return false; /* cycle, preserve caller output */
        staged[step] = next;
        picked[next] = true;
        for (size_t i = 0; i < m; ++i) {
            if (edges[i].from == next) --degree[edges[i].to];
        }
    }
    if (n > 0) memcpy(out, staged, n * sizeof *out);
    return true;
}
