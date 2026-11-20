# SwarmLadder C

A standalone C17 course for learners working locally with a C compiler and Make. Each level has six workshops, 24 graded functions, 30 independent exercises and three projects with graded core implementations.

| Level | What you will learn |
| --- | --- |
| [Basics](basics/README.md) | Integer arithmetic, decisions, loops, arrays, strings and structs |
| [Intermediate](intermediate/README.md) | Output parameters, mutable buffers, parsing, sorted tables, callbacks and file streams |
| [Advanced](advanced/README.md) | Ownership, linked structures, binary records, circular queues, bit sets and transactional updates |

## First exercise

```sh
git clone https://github.com/SwarmLadder/C.git
cd C
make check TASK=whole_minutes
```

The starter prints the name of the unfinished function and exits. Open [Clocks and units](basics/clocks-and-units.md), edit its starter, and rerun the command. To check your first complete level, run `make check LEVEL=basics`. To run the answer key, use `make reference`. Both commands accept the same TASK and LEVEL filters. The executable checks core contracts. Independent exercises and project extensions are for practice and review.

## Conventions

The course uses C17 with exact-width integer types and ASCII text fixtures. A pointer paired with a zero length may be null when no elements are accessed. Otherwise supply valid objects of the declared size, initialized data structures, distinct output arguments where required, and valid C strings for string inputs. A zero-initialized Vector or Ring is empty. Read each exercise for ownership and error behavior.
