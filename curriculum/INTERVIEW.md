# C programming interviews — 36 reasoning questions

These are reasoning and debugging prompts, not trivia. Answer without looking, sketch a specific test, then compare the explanation. Each section corresponds to a course level. The reviewer should insist on language-contract accuracy and a concrete example.

## Foundations

### 1. What is the difference between declaration and definition?

A declaration introduces a name and type for translation. A definition provides a function body or defines an object. Headers ordinarily provide declarations while a .c file provides a single external definition. A missing definition can compile cleanly but fail at link time; defining the same external function in multiple translation units produces a duplicate-definition problem.

### 2. How is an array different from a pointer?

An array object contains its elements; a pointer object stores an address. Array expressions usually decay to pointers, but sizeof an actual array measures the whole array while sizeof a pointer measures the pointer object. A function parameter declared with array syntax is adjusted to a pointer, so pass length separately.

### 3. What is a dangling pointer?

A pointer whose referenced object's lifetime has ended. It may be non-NULL and print a plausible address; dereferencing it is invalid. Examples are returning a local array address and using a malloc allocation after free. Track validity intervals and ownership rather than checking only for NULL.

### 4. What does static mean inside and outside a function?

At block scope, static gives an object static storage duration, retaining state across calls while keeping its name scoped locally. At file scope, static gives a function or object internal linkage, preventing other translation units from referring to that entity by the same external symbol. These are different properties.

### 5. What is undefined signed overflow?

The standard does not require a value after overflow of signed arithmetic. A compiler may optimize assuming a conforming program never overflows. Check representability before evaluating the sum, difference or product, and test INT_MAX/INT_MIN boundaries under a supporting sanitizer.

### 6. How does unsigned overflow behave?

Arithmetic on an unsigned N-bit type is computed modulo 2^N, which is defined. That does not mean unsigned wrap is harmless; wrapped sizes can lead to an undersized allocation or incorrect index. Use SIZE_MAX division guards before multiplication and bounds checks before pointer arithmetic.

### 7. Why should indexes often use size_t, and what trap comes with it?

size_t is capable of representing object sizes and commonly fits array indexes. It is unsigned: a loop of the form i>=0 is never terminated by i becoming negative. Guard n==0 before computing n-1 or use a half-open range decreasing only after checking it is nonempty.

### 8. What is the contract of a C string?

It is a sequence of char values terminated by a NUL byte in accessible storage. strlen needs that terminator; otherwise it can read beyond bounds. Binary buffers and network frames may contain zero bytes or lack terminators, so use pointer-plus-length interfaces for them.

### 9. Why cast char before calling isspace?

ctype.h classification functions accept EOF or values representable as unsigned char. On targets where plain char is signed, high-bit bytes become negative and passing them directly can violate the contract. Cast to unsigned char before classification, while separately documenting locale and encoding assumptions.

### 10. Can two structs with identical field values differ in their bytes?

Yes. Implementations may include padding with non-meaningful bytes. Comparing entire object representations with memcmp or writing them directly as a portable protocol is unreliable. Compare fields semantically and encode persistent/network data with explicit widths and byte order.

### 11. What distinguishes compile, link and runtime errors?

Compilation checks syntax, types and translation-unit constraints. Linkage resolves required external definitions. Runtime errors appear during execution, and some invalid executions invoke undefined behavior without a guaranteed crash. First identify the stage before selecting tools and debugging hypotheses.

### 12. What do the different const pointer declarations mean?

const int *p blocks modifying an int through p; int *const p prevents changing the pointer variable; const int *const p does both. Const alone does not prove thread safety or deep immutability: other legal aliases or pointed-to allocations may still change.

## Intermediate

### 1. How should realloc be used safely?

Assign its result to a temporary pointer. On failure, the original allocation remains valid and owned; replacing the only pointer directly with NULL leaks it. After successful growth, all previous pointers into the old allocation must be treated as invalid, even when the numerical address does not move.

### 2. What is a strong failure guarantee?

If an operation fails, the caller-visible object remains in its previous valid state. Stage new values and allocations before committing them. For a buffer append, validate required capacity and acquire memory before changing length; for a multi-field parser, decode into local variables before writing any output.

### 3. How do you detect multiplication overflow before malloc?

If element_size>0, ensure count <= SIZE_MAX / element_size before computing count*element_size. Otherwise a wrapped byte count may allocate too little storage. Also specify what zero-element requests mean and never dereference a pointer when the required count is zero.

### 4. Why is atoi unsuitable for strict untrusted parsing?

It does not provide the precise distinction between malformed input, accepted zero, trailing garbage and range failure that robust interfaces often require. Define the grammar first, reject invalid bytes and detect overflow before updating the accumulator. Return status independently of the parsed value.

### 5. Why does fgetc return an int, not char?

It must represent all possible unsigned char byte values and the special EOF sentinel. At EOF, inspect ferror to distinguish an I/O failure from normal end-of-file. Converting fgetc to char before checking EOF can lose information on some platforms.

### 6. How do short reads and writes affect correctness?

I/O calls are not always all-or-nothing. fwrite can report fewer elements written; POSIX read/write may transfer fewer bytes than requested or be interrupted. Track the number already processed, update the remaining range, and report failure without claiming the whole operation succeeded.

### 7. Why is a qsort comparator written as a-b dangerous?

Subtracting extreme int values may overflow, invoking undefined behavior and breaking ordering. Return (a>b)-(a<b) or equivalent branch comparisons. A comparator also needs consistent transitive results, and ISO C qsort does not guarantee a stable sort.

### 8. What invariant makes lower_bound correct?

Maintain a half-open candidate interval [lo,hi) such that positions before lo are strictly smaller than the key and the answer remains within [lo,hi]. Comparing at mid either advances lo past smaller values or moves hi to mid. The interval shrinks, and termination returns the first position not smaller than the target.

### 9. Why can macros be dangerous even when parenthesized?

A function-like macro may evaluate arguments multiple times. A square macro invoked with i++ performs an unsequenced modification, which can be undefined. An inline typed function evaluates its arguments once before entering the body and allows type checking.

### 10. What should a callback API specify beyond its type?

Who owns the context pointer, whether it may be NULL, whether the callback may mutate caller data, how long borrowed pointers remain valid, and whether a callback can abort iteration. Function pointer syntax does not express these operational and lifetime requirements.

### 11. Why is a wire format separate from a struct definition?

Struct padding, alignment and integer byte order vary across targets. Define field offsets, widths, byte order and validation rules in the protocol. Decode with byte operations or carefully specified copies, verifying lengths before accessing bytes, and commit outputs only after full validation.

### 12. Why use an opaque struct in a library API?

An incomplete type in the header keeps member layout private and forces clients to use constructor/accessor/destructor functions. That supports stronger invariants and may simplify ABI evolution. Documentation must still state ownership, thread safety and what happens on allocation failure.

## Advanced

### 1. Why can undefined behavior change with optimization?

The optimizer models the C standard and can assume well-defined programs do not overflow signed arithmetic, dereference invalid pointers or violate aliasing constraints. A debug build that appears correct is not evidence of validity. Remove the invalid operation instead of pinning a compiler flag.

### 2. What constitutes a data race in the C memory model?

Conflicting accesses to the same non-atomic object from different threads, with at least one write and no required synchronization. Data races are undefined behavior, not merely stale values. Protect the state with a mutex or design an atomic protocol with an explicit happens-before relationship.

### 3. When is memory_order_relaxed appropriate?

For an independent atomic statistic where only atomicity of the value matters. It does not publish unrelated non-atomic data. A producer publishing a payload usually needs stronger synchronization, such as release/acquire, and an ownership protocol preventing reuse while the consumer reads.

### 4. How does a release/acquire handoff work?

The producer initializes ordinary data, then release-stores an atomic readiness flag. The consumer acquire-loads the flag and reads the payload only after observing publication. The pattern orders those accesses, but a reusable queue still needs protection against concurrent overwrites and a safe shutdown protocol.

### 5. What is ISO C17 versus POSIX?

ISO C defines FILE streams and the core language/library; POSIX adds file descriptors, fork, read/write, pipes and other OS APIs. POSIX-dependent code can be appropriate for systems programming but is not portable ISO C. Isolate platform adapters and state compiler/library requirements in the build docs.

### 6. Does a successful fwrite guarantee durable disk content?

No. Output may still be buffered, and durability depends on OS/filesystem operations beyond the C stream contract. fflush and fclose can detect additional failures but are not a universal power-loss durability guarantee. Separate correctness, atomic visibility and crash durability in the specification.

### 7. Why not read a uint32_t by casting a byte pointer?

The pointer may be misaligned, violate effective-type access rules, or interpret platform-dependent byte order. For a defined wire protocol, validate the available byte count and reconstruct the unsigned value with shifts of sufficiently wide types and a documented endian order.

### 8. What invariants define a ring buffer?

Length is between zero and capacity; head is a valid buffer index when capacity is nonzero; unread elements appear in logical FIFO order around the ring. Guard zero capacity before modulo operations and define what full means: reject, overwrite or block. Each operation must preserve all invariants.

### 9. Why do open-addressed hash tables use tombstones?

Deleting an entry cannot simply mark its bucket never-used: later keys in the same probe sequence may otherwise become unreachable. A tombstone says that probing must continue, while an actually unused slot may terminate a search. Rehash to control load factor and tombstone accumulation.

### 10. How do fuzzing and property tests differ from example tests?

Example tests assert known outputs for selected inputs. Property tests express general relationships such as decode(encode(x))==x; fuzzers generate many inputs seeking crashes, hangs or property violations. They improve empirical coverage but cannot prove freedom from all undefined behavior.

### 11. How should untrusted length arithmetic be checked?

Establish offset<=size, then check field_length<=size-offset before pointer arithmetic or copying. Checking offset+field_length<=size directly can overflow and falsely accept invalid input. Also guard multiplication before allocating arrays and impose resource limits below theoretical maximum values.

### 12. How do you optimize C without compromising correctness?

Measure a representative bottleneck, verify the baseline result, select a change based on data access patterns or asymptotic cost, then rerun identical regression and sanitizer tests. Record toolchain, flags, input size and timing variability. Do not rely on undefined behavior, and isolate architecture-specific optimizations behind portability checks.

## Mock interview rounds

**Round 1 (45 minutes):** 15 minutes pointer/array reasoning, 15 minutes strict decimal parser, 15 minutes overflow and bounds tests. State one invariant before coding.

**Round 2 (60 minutes):** Implement a resizable text buffer with error preservation, then explain realloc failure, stale aliases, input source overlap and amortized complexity.

**Round 3 (75 minutes):** Decode a binary header from a truncated stream, demonstrate safe failure, design a deterministic topological scheduler, then discuss platform portability and thread safety.

### Evaluation

Strong answers state preconditions, postconditions, ownership, complexity, a counterexample to the obvious mistake, and a relevant executable test. Incorrect claims that all C has two's-complement signed wrap, all systems support POSIX, or sanitizers prove correctness are major review findings.

See the [assessment rubric](ASSESSMENT.md), [mastery labs](../mastery/README.md) and [12-week roadmap](ROADMAP.md).
