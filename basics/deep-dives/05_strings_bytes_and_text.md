# Deep Dive 05: C strings are not general byte buffers

**Outcome:** Work safely with NUL terminators, capacity, text encoding and binary payloads. **Time:** 90–120 minutes.

## A string has a termination contract

A C string must contain a NUL byte reachable within valid storage. strlen counts the bytes before this terminator, not the capacity of the array and not the number of Unicode characters. An arbitrary array of bytes may contain embedded zeros or no zero at all; passing it to strlen without a valid terminator is unsafe.

For user input, distinguish a *byte span* (pointer plus length) from a *C string* (pointer with a termination precondition). Networks, compressed data and file formats typically need byte spans. A UTF-8 character may occupy multiple bytes, so byte indexing is not a universal text-processing API.

## Checked copying with a clear contract

~~~c
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

bool copy_text(char *dst, size_t capacity, const char *src) {
    if (!dst || !src) return false;
    size_t n = strlen(src); /* src must be terminated */
    if (n >= capacity) return false; /* reserve one byte for NUL */
    memcpy(dst, src, n + 1);        /* caller promises no overlap */
    return true;
}
~~~

On capacity failure, destination bytes are unchanged. However, this API is only as safe as its stated preconditions. If overlap is possible, use memmove or reject overlapping ranges before copying; never claim a function accepts arbitrary bytes when it invokes strlen.

The common function strncpy is not automatically a safe substitute. When the source length equals or exceeds the provided count, it may leave the destination unterminated. It also zero-pads shorter inputs. Make the required end state explicit instead.

## Byte values and character classification

ctype.h routines such as isdigit and isspace expect EOF or values representable as unsigned char. If plain char is signed, passing a negative char can violate the contract. Cast to unsigned char before classification.

Encoding restrictions belong in the API documentation. ASCII-only token parsing is legitimate for a course if stated. UTF-8 validation, normalization and character boundaries require separate rules. Never reverse arbitrary UTF-8 text by swapping individual bytes.

## Practice

1. Contrast sizeof and strlen on char text[]="cat" and char raw[3]={'c','a','t'}.
2. Pass explicit length to a function that processes bytes including an embedded zero.
3. Write ASCII lowercase conversion and test bytes outside ASCII as unchanged.
4. Test copy_text with empty input, exact fit, one-byte shortage and a source with no terminator (do not call it on the invalid source; explain the precondition).
5. Explain why printf with %s is insufficient to show a binary file.

**Interview check:** Is char data[3]={'a','b','c'} a valid C string? No; it lacks a reachable NUL.

**Exit criterion:** You consistently choose string or byte-span interfaces according to the data contract.