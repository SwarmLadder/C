# Deep Dive 03: Scope, lifetime, pointers and ownership

**Outcome:** Explain where objects live, when they cease to exist and who must release memory. **Time:** 100–130 minutes.

## Different concepts with different rules

Scope describes where an identifier is visible. Linkage relates declarations in different scopes or translation units. Storage duration describes how long object storage exists. An automatic local object stops existing when its block ends. A file-scope static object persists for the program's lifetime. Dynamically allocated storage remains until released. A pointer variable can survive longer than the object it used to reference.

A stack and heap are useful typical implementation details, not normative descriptions of all C storage. Optimizers can eliminate objects or keep them in registers while preserving the language's observable behavior.

## A dangerous return and its replacement

~~~c
/* Incorrect: local buffer lifetime ends on return. */
const char *broken(void) {
    char text[] = "hello";
    return text;
}
~~~

Instead either return a *value*, accept a caller-supplied buffer, or return allocated memory with a clear owner:

~~~c
#include <stdlib.h>
#include <string.h>

char *make_copy(const char *text) {
    size_t n = strlen(text); /* requires a valid C string */
    if (n == SIZE_MAX) return NULL;
    char *copy = malloc(n + 1);
    if (copy == NULL) return NULL;
    memcpy(copy, text, n + 1);
    return copy;             /* caller calls free(copy) */
}
~~~

The function assumes text points to a valid terminated string. The caller owns the returned allocation and must free it exactly once; borrowed aliases must not be used after the free. In practice, SIZE_MAX and stdint.h or stdint/size macros must be included as needed by the implementation.

## Aliasing and resizing

After successful realloc, *every old pointer value into the original allocation is invalid*, even if the numerical address appears unchanged. Never assign the result directly to the only saved pointer; on failure realloc returns NULL and leaves the original allocation owned by the caller. Use a temporary result. Keep one owner and clearly marked borrows.

A double-free, use-after-free, freeing a pointer into the middle of an allocation, and forgetting to free at all are distinct faults. In a container of pointers, ask whether the container owns pointed-to elements or merely indexes them. Container destruction depends on this answer.

## Error-path walkthrough

Suppose construction allocates a struct, then a buffer, then a second buffer. If the second buffer fails, you must release the first buffer and struct, while leaving no half-initialized object visible to the caller. A single cleanup label can make repeated error paths auditable, or use carefully nested early-return cleanup. The goal is *one obvious owner at every point*.

## Practice

1. Draw a lifetime timeline for an automatic array, a static counter, and malloc storage.
2. Write a constructor/destructor pair and test a simulated second-allocation failure.
3. Show why returning &local[0] is invalid after a function returns.
4. Draw the pointer graph before and after realloc on both success and failure.
5. Explain what happens to aliases after free.

**Interview check:** Can an in-scope pointer point to an object whose lifetime ended? Yes. Name lifetime and pointee lifetime are different.

**Exit criterion:** Every pointer in your code has a named owner, validity interval and release path.