# Mastery A3 — Fixed-capacity circular queue

**Level:** Advanced · **Time:** 100–150 minutes · **Implementation:** `mastery/starter/ring_queue.c`

## Build a FIFO, not an array that shifts on every pop

Implement `ring_reset`, `ring_push`, and `ring_pop` for a RingQueue with capacity **exactly eight**. `ring_reset` initializes a live RingQueue's head and size to zero, and safely accepts NULL by doing nothing. Push appends a value if there is free space. Pop removes the oldest value and writes it to the output. Push when full, pop when empty, or operations with invalid pointers must return false without changing queue state or pop's previous output.

Do not move seven elements every time you pop. Instead, store elements in a circular array with head and size fields; the next append slot is `(head+size)%8`. The oldest value is at head, and head advances modulo eight after a successful pop.

## Trace with wraparound

Initially head=0 and size=0. Push `[0,10,20,30,40,50,60,70]`: size becomes 8; another push fails. Pop three times: outputs 0,10,20, head becomes 3, size becomes 5. Push 80,90,100. The insert indexes wrap around to 0,1,2. Pops now return `30,40,50,60,70,80,90,100` in that exact order.

The physical buffer after wraparound does not resemble the logical FIFO order. That is not a bug; the **logical sequence** begins at head and includes size elements.

## Representation invariant

For every initialized queue, `0 <= size <= 8` and `0 <= head < 8`. For 0<=i<size, logical element i is stored at index `(head+i)%8`. A successful push increases size by one without moving earlier elements. A successful pop advances head and decreases size without moving the remaining elements. Both operations take O(1) time and O(1) auxiliary space. RingQueue storage is fixed and owned by the caller.

Validate the head and size before using them as indexes. The constant capacity eight also establishes that `head+size` cannot overflow size_t on any conforming implementation supporting these values.

## Adversarial tests

1. Pop from an empty queue, with output initialized to 777; 777 must remain.
2. Fill eight slots; ninth insertion fails without overwriting the oldest value.
3. Three pops, three pushes, eight pops: verify exact FIFO order and wraparound.
4. Include uint32_t zero and UINT32_MAX.
5. Test NULL pointers and intentionally invalid head values without indexing them.
6. Reset after use and repeat the sequence.

Run `make mastery-check TASK=ring_queue`.

## Interview and system extension

Compare the ring with an array-based queue that calls memmove after every pop: that design may require O(n) time per dequeue. Generalize to a runtime capacity and explain what happens at cap=0, during size arithmetic, and under allocation failure. For a **concurrent** bounded queue, explain why a shared head/tail pair is not thread-safe merely because reads and writes are small; synchronization or a formally proven atomic protocol is needed.

**Review gate:** Prove FIFO ordering from the representation invariant and explain every full/empty boundary.