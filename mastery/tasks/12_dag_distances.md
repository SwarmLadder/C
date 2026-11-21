# Mastery A4 — Shortest paths through a dependency DAG

**Level:** Advanced · **Time:** 120–180 minutes · **Implementation:** `mastery/starter/dag_distances.c`

## What makes this an engineering exercise?

Find shortest weighted distances from a source vertex in a **directed acyclic graph**. Nodes are indexed 0..n-1 with 1<=n<=64. Edges are pairs `(from,to)`, each paired with an unsigned 32-bit weight. A valid output contains one int64_t distance per vertex; unreachable vertices are represented by -1, and the source is 0. Repeated edges are permitted. Reject any cycle, invalid endpoint, invalid source, NULL required pointers or unsupported n, preserving every caller output element on failure.

This goes beyond memorizing Dijkstra. Because a DAG admits a topological ordering, distances can be relaxed in a single pass over that ordering, even when the graph has many alternate routes. The graph may be disconnected and the source may be in the middle of the topological order.

## Two-stage worked example

Edges: `0→1 (4)`, `0→2 (2)`, `1→3 (1)`, `2→3 (7)`, `3→4 (3)`. The DAG has topological order `0,1,2,3,4` when ties are resolved by lowest index.

From source 0, begin distances `[0,-1,-1,-1,-1]`. Relax from 0 to set 1=4 and 2=2. Relax from 1 to set 3=5. Relax from 2 proposes 3=9; retain the smaller 5. Relax from 3 to set 4=8. Final distances are `[0,4,2,5,8]`. From source 2, vertices 0 and 1 remain unreachable: `[-1,-1,0,7,10]`.

## Phase 1: reject invalid graphs

Validate edge endpoint ranges and build indegrees. Repeated edges increment indegree twice and must be decremented twice. Repeatedly choose an unprocessed zero-indegree vertex, remove it, and decrease the indegree of each outgoing neighbor. If no such vertex exists before selecting all n vertices, the graph contains a directed cycle and must be rejected.

**Do not write partial distances to the caller before validation succeeds.** Maintain a local result and publish it only when all checks are finished. The same contract applies to graph metadata and error status.

## Phase 2: dynamic programming on a topological order

Initialize temporary distances to -1 except source=0. Visit vertices in topological order. For each reachable vertex, relax every outgoing edge with `candidate = distance[from] + weight`. Update only if the destination is unreachable or the candidate is smaller.

With nonnegative uint32_t weights and at most 64 vertices, a shortest path never needs a repeated vertex. Any path in a DAG has at most 63 edges, and `63 * UINT32_MAX` fits in int64_t, so the accumulated sum is representable. This explicit arithmetic proof matters as much as the graph invariant.

A simple scan selecting the smallest eligible vertex costs O(n²), and scanning the edge list after each selection and relaxation gives O(nE), for O(n²+nE) total time; stack space is O(n) for the bounded arrays. A scalable adjacency list and priority structure could improve performance on larger sparse graphs, but add complexity and allocations.

## Tests and follow-up

Test the five-node fixture, a graph whose source cannot reach any other node, zero-weight edges, duplicate edges with different weights, UINT32_MAX weights, a self-loop, a two-node cycle, endpoints equal to n, n=0, n=65, and missing weights with positive edge count. Initialize outputs to sentinels before each invalid case and prove they remain unchanged.

Run `make mastery-check TASK=dag_distances`.

**Interview prompts:** Why does topological relaxation work on a DAG? Why would a cycle invalidate this algorithm? How does the problem differ from shortest paths with arbitrary negative-weight edges? Prove a fixed int64_t accumulator is sufficient under the documented limits.

**Review gate:** Show the topological-order invariant, the relaxation invariant, output atomicity on failure and a representable-distance proof.