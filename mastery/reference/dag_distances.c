#include "mastery.h"
#include <stdint.h>
#include <string.h>
bool dag_distances(size_t n, const Edge *edges, const uint32_t *weights,
                   size_t m, size_t source, int64_t *out) {
    if (n == 0 || n > 64 || source >= n || !out ||
        (m && (!edges || !weights))) return false;
    size_t incoming[64] = {0};
    bool picked[64] = {false};
    size_t order[64];
    for (size_t i = 0; i < m; ++i) {
        if (edges[i].from >= n || edges[i].to >= n ||
            incoming[edges[i].to] == SIZE_MAX) return false;
        ++incoming[edges[i].to];
    }
    for (size_t step = 0; step < n; ++step) {
        size_t chosen = n;
        for (size_t vertex = 0; vertex < n; ++vertex) {
            if (!picked[vertex] && incoming[vertex] == 0) {
                chosen = vertex;
                break;
            }
        }
        if (chosen == n) return false;
        order[step] = chosen;
        picked[chosen] = true;
        for (size_t i = 0; i < m; ++i)
            if (edges[i].from == chosen) --incoming[edges[i].to];
    }
    int64_t distance[64];
    for (size_t i = 0; i < n; ++i) distance[i] = -1;
    distance[source] = 0;
    for (size_t step = 0; step < n; ++step) {
        const size_t from = order[step];
        if (distance[from] < 0) continue;
        for (size_t i = 0; i < m; ++i) {
            if (edges[i].from != from) continue;
            const size_t to = edges[i].to;
            const int64_t candidate = distance[from] + (int64_t)weights[i];
            if (distance[to] < 0 || candidate < distance[to])
                distance[to] = candidate;
        }
    }
    memcpy(out, distance, n * sizeof *out);
    return true;
}
