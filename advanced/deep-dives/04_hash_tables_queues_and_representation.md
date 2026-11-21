# Deep Dive 04 — Hash tables, queues and real memory costs

**Outcome:** Choose data structures based on invariants, allocation behavior and workload—not Big-O alone. **Time:** 140 minutes.

## Contiguous or linked?

A dynamic array has O(1) index access and amortized O(1) append with geometric resizing; insertion in the middle shifts O(n) items. A singly linked list inserts after a known node in O(1), but locating that node is O(n) and each node needs separate storage. Contiguous arrays often achieve better cache locality, so asymptotic labels are not the entire performance story.

## Ring buffer invariant

Maintain head and len with 0<=len<=cap. For nonzero capacity, head is a valid buffer index. Push at (head+len)%cap only if len<cap; pop from head only if len>0. Guard cap==0 before the modulo operation. Because head+len could overflow size_t for extreme capacities, production code can compute the index using a conditional subtraction or establish a representable bound.

## Worked code: bounded FIFO push and pop

This implementation uses a fixed capacity of eight, rejects insertion when full, and preserves the output parameter when the queue is empty. Because both head and len are bounded by eight, their sum cannot overflow size_t.

~~~c
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    unsigned slots[8];
    size_t head;
    size_t len;
} Ring8;

bool ring8_push(Ring8 *q, unsigned item) {
    if (q == NULL || q->len >= 8 || q->head >= 8)
        return false;
    size_t index = (q->head + q->len) % 8;
    q->slots[index] = item;
    ++q->len;
    return true;
}

bool ring8_pop(Ring8 *q, unsigned *out) {
    if (q == NULL || out == NULL || q->len == 0 || q->head >= 8)
        return false;
    *out = q->slots[q->head];
    q->head = (q->head + 1) % 8;
    --q->len;
    return true;
}
~~~

Start with {head=0,len=0}; pushing 8 items sets len=8, so a ninth push fails before modifying data. Three pops move head to 3 and reduce len to 5; three pushes wrap around to slots 0, 1 and 2. The queue's logical reading order is not the same as the physical order of the array. Test the invariant after every transition. In an API with arbitrary capacity rather than fixed eight, head+len may overflow and requires a different index calculation or a documented representable bound.

A fixed-capacity ring should define what happens when full: reject, overwrite oldest, or block. These are different API contracts and should be tested separately.

## Hash collisions and tombstones

Open addressing stores entries in an array. When a collision occurs, a probe sequence searches other slots. Each slot needs states: never used, occupied, or tombstone. Suppose keys 12 and 20 map to slot 4 of an eight-slot table. The second key is stored at 5. If 12 is deleted, lookup for 20 must continue past tombstone 4. Marking deleted slot 4 as *never used* incorrectly stops the lookup.

Hash lookup is expected O(1) given suitable hashing and load-factor assumptions, not guaranteed worst-case O(1). Rehash as occupancy grows, and allocate the new table *before* changing the old one so a failed rehash leaves valid state.

## Proving a data structure

A queue proof identifies the state invariant, shows each operation preserves it, then explains why outputs correspond to FIFO ordering. A hash table proof identifies which probe locations must be visited for a key to be findable. Without invariants, obscure boundary errors can persist despite many normal-input tests.

## Practice

1. Trace a ring of capacity three through push, pop, push, push and one rejected push.
2. Design three-state hash slots; show lookup after a deletion.
3. Estimate memory used by one million fixed records stored contiguously versus as linked nodes.
4. Design a rehash that preserves original entries if malloc fails.
5. Compare sorted-vector search and hash search for small, read-heavy tables.

**Interview checkpoint:** Why can a linear scan outperform a linked structure with better theoretical lookup properties? Cache locality and constant factors.

**Exit criterion:** You can state and test every structural invariant including overflow and allocation-failure cases.