#include "mastery.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A readable reference CLI for the binary-frame parsing capstone.
 * C17 only: the stream is stdin; this program never treats payload as text.
 * It stages all counts and prints only after the complete input validates.
 */
static bool read_frames(FILE *input, uint64_t *counts,
                        uint64_t *frame_count, uint64_t *payload_bytes) {
    unsigned char header[9];
    unsigned char scratch[4096];

    for (;;) {
        const size_t got = fread(header, 1, sizeof header, input);
        if (got == 0) {
            if (ferror(input)) {
                fputs("Read failure while reading header\n", stderr);
                return false;
            }
            return true; /* clean EOF at a frame boundary */
        }
        if (got != sizeof header) {
            fputs("Truncated frame header\n", stderr);
            return false;
        }

        FrameHeader record;
        if (!decode_frame_header(header, sizeof header, &record)) {
            fputs("Invalid frame header (magic, version or size)\n", stderr);
            return false;
        }
        if (*frame_count == UINT64_MAX ||
            counts[record.kind] == UINT64_MAX ||
            *payload_bytes > UINT64_MAX - (uint64_t)record.payload_length) {
            fputs("Counter overflow: refusing to publish summary\n", stderr);
            return false;
        }

        uint32_t remaining = record.payload_length;
        while (remaining > 0) {
            const size_t need = remaining < sizeof scratch
                ? (size_t)remaining : sizeof scratch;
            const size_t copied = fread(scratch, 1, need, input);
            if (copied != need) {
                fputs(ferror(input) ? "Payload read error\n" :
                      "Truncated frame payload\n", stderr);
                return false;
            }
            remaining -= (uint32_t)copied;
        }

        ++counts[record.kind];
        ++*frame_count;
        *payload_bytes += (uint64_t)record.payload_length;
    }
}

int main(int argc, char **argv) {
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        puts("Usage: telemetry-inspector < frames.bin");
        puts("Reads SL v1 binary frames and counts frames per kind.");
        return 0;
    }
    if (argc != 1) {
        fputs("Usage: telemetry-inspector < frames.bin\n", stderr);
        return 2;
    }

    /* Explicitly reject platforms whose size_t cannot represent the array. */
    if ((uintmax_t)SIZE_MAX / sizeof(uint64_t) <= (uintmax_t)UINT16_MAX) {
        fputs("This target cannot allocate the counter table\n", stderr);
        return 1;
    }
    const size_t kinds = (size_t)UINT16_MAX + (size_t)1;
    uint64_t *counts = calloc(kinds, sizeof *counts);
    if (counts == NULL) {
        fputs("Counter allocation failed\n", stderr);
        return 1;
    }
    uint64_t total_frames = 0;
    uint64_t total_bytes = 0;
    if (!read_frames(stdin, counts, &total_frames, &total_bytes)) {
        free(counts);
        return 1;
    }

    if (printf("frames=%" PRIu64 " payload_bytes=%" PRIu64 "\n",
               total_frames, total_bytes) < 0) {
        free(counts);
        return 1;
    }
    for (size_t kind = 0; kind < kinds; ++kind) {
        if (counts[kind] == 0) continue;
        if (printf("kind=%u frames=%" PRIu64 "\n",
                   (unsigned)kind, counts[kind]) < 0) {
            free(counts);
            return 1;
        }
    }
    free(counts);
    if (fflush(stdout) == EOF) {
        fputs("Output flush failure\n", stderr);
        return 1;
    }
    return 0;
}
