# Mastery lab A2 — Deterministic dependency ordering

**Difficulty:** advanced / graph algorithms. **Target:** topology_sort. **Suggested time:** 90–150 minutes.

## Problem contract

There are n vertices numbered 0 through n-1, where n ranges from 0 to 64. Directed edges (u,v) mean u must appear before v. Return true and store a topological ordering on success. If multiple vertices have zero remaining indegree, always choose the **smallest numeric vertex**, making output deterministic.

Return false for n>64, a NULL required pointer, an out-of-range edge endpoint, or any directed cycle. On any failure leave the caller's output buffer untouched. Repeated edges are valid and count as distinct constraints, though they do not change which orders are legal.

## Invariant and algorithm

Compute the indegree for each vertex. At each step, choose the smallest not-yet-picked vertex with zero indegree, append it to a temporary result, mark it picked and decrement indegrees for its outgoing edges. If no eligible vertex exists while unpicked vertices remain, the remaining subgraph has a cycle; reject without copying the temporary result to the caller.

Because n<=64, a simple scan for the smallest eligible vertex is appropriate. With a naively scanned edge list, complexity is O(n²+nE), auxiliary space O(n); document the tradeoff. An adjacency list and min heap can reduce the asymptotic cost for larger graphs.

## Example trace

Dependencies (0,2), (1,2), (2,3) yield initial indegrees [0,0,2,1]. Choose 0, then 1, then 2, then 3. Output is [0,1,2,3]. If edges are (0,1) and (1,0), no vertex has zero indegree: reject the cycle and retain existing output.

## Test plan

- Empty graph with n=0; no output required.
- Four vertices and no edges; ordering must be 0,1,2,3.
- A DAG with multiple initially eligible nodes.
- A simple two-node cycle and a self-loop.
- A duplicate edge that must be decremented twice.
- An edge referring to vertex n, a NULL edges pointer with positive edge count, and n=65.
- An output buffer initialized to sentinel values that must survive failure.

Run:

~~~sh
make mastery-check TASK=topological
~~~

## Extensions

Implement Kahn's algorithm using an adjacency list and min heap. Implement DFS-based cycle detection with white/gray/black node colors. Compare both under a deterministic randomized DAG generator.

**Proof prompt:** Why does a zero-indegree vertex respect all constraints when selected, and why does having no such vertex imply a cycle?

**Interview follow-up:** Why is deterministic ordering useful in build systems? It makes outputs reproducible and easier to test or compare across machines.