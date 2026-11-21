# Deep Dive 01: Headers, linkage and API boundaries

**Outcome:** Design multi-file C interfaces without duplicate symbols, hidden ownership or ABI surprises. **Time:** 90–120 minutes.

## Separate interface from implementation

A header declares the types and functions users need; a .c file provides an external definition. Build users may compile against your header without seeing your private helpers. Keep headers independently includable: include any standard headers their declarations require, protect them with include guards, and avoid implementation details when possible.

~~~c
/* meter.h */
#ifndef METER_H
#define METER_H
#include <stdbool.h>
#include <stddef.h>
typedef struct Meter Meter;  /* incomplete: implementation is hidden */
Meter *meter_create(size_t capacity);
bool meter_record(Meter *meter, unsigned value);
void meter_destroy(Meter *meter);
#endif
~~~

Clients can hold a Meter pointer but cannot create a Meter object by value or access its members because its definition is private. This helps preserve invariants and permits implementation changes without recompiling every user under some binary-interface arrangements.

## Linkage versus storage duration

A file-scope declaration with static gives *internal linkage* to names such as helper functions. A file-scope variable can have static storage duration but external linkage when declared without static. In contrast, a local static counter is visible only inside its function but persists across calls. These concepts answer different questions.

Do not place a non-static global definition such as int total=0 into a header included by multiple .c files. Declare extern int total in the header, define int total=0 in exactly one .c file, and consider whether exposing a writable global was wise in the first place.

## Function pointers and callback contracts

A callback type describes its argument and return types. It does not by itself say whether the callback can mutate state, whether it may keep pointers after return or whether NULL callbacks are allowed. Use a context pointer to avoid global variables and document the callback's validity.

~~~c
typedef bool (*Predicate)(int value, void *context);

size_t count_matching(const int *items, size_t count,
                      Predicate condition, void *context) {
    size_t matches = 0;
    for (size_t i = 0; i < count; ++i)
        if (condition(items[i], context)) ++matches;
    return matches;
}
~~~

Here the callback must be valid when count>0. The caller owns context; the implementation only borrows it for the duration of the call.

## Binary compatibility versus source compatibility

Changing a struct field layout exposed in a public header can break compiled client code even when the function names still link. An opaque pointer hides the representation, allowing versioned API evolution. Distinguish ABI compatibility (existing binaries) from source compatibility (existing source can rebuild).

## Practice

1. Split a one-file program into a header, library source and client source; build each object independently.
2. Add two private static helpers and demonstrate they cannot be linked from other translation units.
3. Create an opaque struct, constructor and destructor, and document failure cleanup.
4. Design a callback interface with borrowed context, including a case where condition returns false.
5. Produce a deliberate multiple-definition link failure and fix it without adding ad hoc source includes.

**Interview check:** What does static mean at file scope compared with a local variable? File scope: internal linkage; block scope: static storage duration, with block visibility.

**Exit criterion:** Every public symbol has one authoritative declaration, a documented contract and one intended definition.