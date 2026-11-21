# Deep Dive 03 — Systems I/O and the POSIX boundary

**Outcome:** Build reliable I/O loops and accurately distinguish ISO C17 from POSIX APIs. **Time:** 120 minutes.

## Know your portability contract

ISO C17 supplies FILE streams and functions including fopen, fread, fwrite, fflush, ferror and fclose. POSIX adds file descriptors and APIs such as open, read, write, fork, pipes and poll. A POSIX systems program is not necessarily portable ISO C; isolate platform-specific interfaces behind explicit adapters.

A successful fread of fewer objects than requested may indicate end-of-file or an error; inspect feof and ferror. A short fwrite must be handled rather than treated as complete. Even a successful write may be buffered; a later fflush or fclose can report failure.

## Partial writes in POSIX

~~~c
/* POSIX-only fragment, requires unistd.h and errno.h. */
size_t written = 0;
while (written < length) {
    ssize_t n = write(fd, data + written, length - written);
    if (n > 0) { written += (size_t)n; continue; }
    if (n < 0 && errno == EINTR) continue;
    /* report write failure or lack of progress */
    break;
}
~~~

The caller must provide fd, data and length and handle the failure path; this is not a standalone program. Treating one write call as guaranteed to write the requested byte count is unsafe for pipes, sockets and various other resources. An interrupted syscall can require retry according to the interface's contract.

## Atomicity versus durability

Writing a temporary file and renaming it may provide atomic *visibility of a name change* on certain file systems, but does not automatically guarantee persistence after power loss. Full durability may require syncing file contents and directory metadata, with details varying by platform. State your guarantee: "no partial file visible to concurrent readers" differs from "survives power failure."

## Process and resource ownership

Every successful open creates a resource that must be closed. If a function opens two files, a failure opening the second must close the first. If an API accepts an existing file descriptor, document whether the caller keeps ownership. Use a dedicated error path for cleanup and preserve useful error context.

## Practice

1. Write a portable stream copier for empty, binary and large files.
2. Implement a deliberately short-writing mock and test the retry loop.
3. Explain why fwrite success does not imply durable media storage.
4. Enumerate all cleanup paths in a function that opens an input and output file.
5. Identify symlink/time-of-check versus time-of-use risks in untrusted path handling.

**Interview checkpoint:** Is read() ISO C17? No, it is a POSIX interface.

**Exit criterion:** Your I/O routines handle partial progress, failures and cleanup while clearly declaring portability scope.