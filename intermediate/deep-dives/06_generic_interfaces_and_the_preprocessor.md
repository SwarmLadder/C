# Deep Dive 06: Macros, generic design and maintainable C APIs

**Outcome:** Decide when a macro is appropriate and avoid side-effect and type bugs. **Time:** 90–120 minutes.

## The preprocessor performs substitution, not type checking

~~~c
#define SQUARE(x) ((x) * (x))
~~~

This superficially looks like a function, but SQUARE(i++) expands so i++ is evaluated twice, causing undefined behavior due to unsequenced modifications in C. A safer typed function is:

~~~c
static inline int square_int(int value) {
    return value * value;  /* caller must still prevent signed overflow */
}
~~~

Inline functions preserve single evaluation of arguments and participate in type checking. The inline keyword is not a promise about whether machine code is actually inlined. When C11 _Generic is appropriate, it can select a typed helper based on an expression's type, but complexity can outweigh the benefit.

## Parenthesize, but do not stop there

Macro parameters and replacement expressions should be parenthesized to avoid precedence bugs, yet parentheses do not fix repeated evaluation, hidden control flow, or macro name collisions. Do not build a public library entirely from macros when ordinary functions suffice. Reserve macros for compile-time configuration, guarded constants, conditional compilation, and small generic conveniences with clearly documented restrictions.

## API design with void pointers

The standard library qsort accepts void pointers so it can operate on arbitrary element types. It delegates meaning to a comparison callback and requires the caller to provide the element size. This gives genericity without generics, but places more obligations on the caller: correct casts, no comparator overflow, and no inconsistent ordering.

For an opaque data structure, provide a header containing an incomplete struct declaration and public operations, while its private representation remains in a .c file. This reduces coupling and makes ownership boundaries explicit.

## Preprocessor feature tests

Use #if and #ifdef for compile-time platform choices, not runtime configuration. Build all supported branches in CI: code hidden behind a macro can rot when only one configuration compiles. Prefer documented standard APIs before platform-specific extensions and isolate platform-dependent code in separate translation units.

## Practice

1. Expand SQUARE(i++) by hand and explain the invalid repeated mutation.
2. Compare a macro MAX(a,b) with a typed function; discuss type coercion and side effects.
3. Implement an opaque counter module with create/add/get/destroy operations.
4. Write an _Generic expression selecting two typed display helpers, then explain when separate function names would be clearer.
5. Build both sides of a conditional feature macro and run tests for both.

**Interview check:** Why are inline functions usually safer than function-like macros? Type checking and single argument evaluation.

**Exit criterion:** You can identify every macro evaluation and use an interface strategy appropriate to your library's maintenance needs.