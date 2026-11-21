# Deep Dive 01: The compiler, linker and reproducible builds

**Outcome:** Build a multi-file C17 program and distinguish preprocessing, compilation, linking and runtime failures. **Time:** 100–130 minutes.

## Four stages, four ways to fail

The preprocessor expands includes and macros before compilation. The compiler analyzes one *translation unit* and produces an object file. The linker resolves external references among object files and libraries. Finally, the operating system loads the executable. A missing semicolon typically fails compilation; a missing definition usually fails linkage; an invalid memory access may fail at runtime.

A header is an interface, not a place to define ordinary external functions. An include guard prevents repeated inclusion *inside one translation unit* but does not stop the linker from seeing duplicate global definitions if that header defines a function and is included in multiple source files.

## Worked project: a tiny library

Create clamp.h:

~~~c
#ifndef CLAMP_H
#define CLAMP_H
int clamp_int(int value, int low, int high);
#endif
~~~

Create clamp.c:

~~~c
#include "clamp.h"
int clamp_int(int value, int low, int high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}
~~~

Create main.c:

~~~c
#include <stdio.h>
#include "clamp.h"
int main(void) {
    printf("%d\n", clamp_int(27, 0, 10));
    return 0;
}
~~~

Build the translation units separately:

~~~sh
cc -std=c17 -Wall -Wextra -Werror -pedantic -c clamp.c -o clamp.o
cc -std=c17 -Wall -Wextra -Werror -pedantic -c main.c -o main.o
cc main.o clamp.o -o app
./app
~~~

The result is 10. Removing clamp.o from the final command leaves the reference unresolved at *link time*. Use -E to inspect preprocessing, -S to produce assembly and -c to produce object code. These flags are common GCC/Clang conventions, not part of ISO C itself.

## Reason about dependencies

A Make rule must express that main.o depends on both main.c and clamp.h. Otherwise changing a header can leave an outdated object file, a particularly confusing bug when structure definitions have changed. Do not define an object file dependency only on the .c file. For a reproducible build, document the C standard, compiler options and external dependencies; clean before performing a release test.

## Common traps

Do not include source .c files as if they were headers. Do not define writable global objects in headers without a deliberate linkage strategy. Remember that an object can compile independently yet fail to link, and a program that links can still violate its runtime contracts. Treat warnings as evidence to investigate, not decoration.

## Independent practice

1. Deliberately omit clamp.o; paste the linker diagnostic and explain the missing definition.
2. Move the function body into the header, include it from both .c files and explain why the duplicate symbol is not fixed by an include guard.
3. Change the function signature in clamp.h without updating clamp.c; explain which phase catches the mismatch.
4. Create a Makefile with separate object targets, explicit header dependencies and a clean target.
5. Repeat the build with GCC and Clang; explain any differences in diagnostics.

**Interview check:** What is the difference between a declaration and a definition? A declaration introduces the entity and type; a definition also provides the storage or function body required for linkage.

**Exit criterion:** You can reproduce a build from a clean folder, locate the failing stage and state the dependency graph without guessing.