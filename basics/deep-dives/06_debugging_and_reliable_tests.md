# Deep Dive 06: Debuggers, sanitizers and regression testing

**Outcome:** Turn a crash or wrong answer into a minimal test and use tools to diagnose it. **Time:** 120–150 minutes.

## Establish a reproducible experiment

A useful bug report includes input bytes, exact expected output, actual output, compiler, compiler flags and a command that rebuilds from a clean checkout. Reduce the failure until one function illustrates it. A passing happy-path test is not enough for C because ownership mistakes and overflow frequently hide in unusual inputs and error paths.

Every function test needs a *normal case*, a *boundary case*, and if relevant a *failure case that preserves state*. Tests can have independent expected values rather than copying the implementation's output back as the oracle.

~~~c
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

bool checked_add(int a, int b, int *out);

static void test_add(void) {
    int result = 77;
    assert(!checked_add(INT_MAX, 1, &result));
    assert(result == 77);
    assert(checked_add(-3, 5, &result));
    assert(result == 2);
}
~~~

For a production test harness, remember that assert expressions can disappear when NDEBUG is defined. A framework with checks that remain active is often preferable.

## Diagnostics and their limits

With GCC or Clang, build a *separate* diagnostic executable at moderate optimization:

~~~sh
cc -std=c17 -O1 -g -Wall -Wextra -Werror -pedantic \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  program.c -o program-sanitized
./program-sanitized
~~~

AddressSanitizer catches many memory errors such as buffer overruns and use-after-free; UBSan catches many invalid operations such as signed overflow. Tool availability differs across platforms. A clean sanitizer run **does not prove memory safety or functional correctness**, nor does it substitute for checking allocation failures and API contracts.

## Use a debugger instead of guessing

Set a breakpoint before the failing operation with GDB or LLDB, single-step, inspect values and obtain a stack backtrace. A crash in free may originate from a prior write; the most valuable report identifies the *first invalid operation*, not only the final symptom. Compare behavior at -O0 and -O2, but never treat "works at -O0" as evidence that undefined behavior is valid.

## Practice

1. Add a one-byte overrun to a disposable program, reproduce it with AddressSanitizer and then fix it.
2. Explain why signed overflow can yield different behavior with optimizations.
3. Test every early-return path in a two-allocation constructor and document cleanup.
4. Create a table of at least six inputs for a decimal parser: empty, zero, maximum, too-large, negative and trailing characters.
5. Use a debugger to locate the first failing loop iteration, then write a regression test.

**Interview check:** Which tests are especially important in C? Invalid lengths, overflow boundaries, allocation failures, dangling ownership and overlapping buffers because they can lead to undefined behavior.

**Exit criterion:** You can isolate a bug, read a sanitizer report and defend a fix with a permanent regression test.