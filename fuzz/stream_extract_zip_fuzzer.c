#include "zip.h"
#include <stdint.h>
#include <stdlib.h>

int on_extract_entry(const char *filename, void *arg) {
    static int i = 0;
    int n = *(int *)arg;
    printf("Extracted: %s (%d of %d)\n", filename, ++i, n);
    return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, const size_t size)
{
    int arg = 2;
    zip_stream_extract(data, size, "/tmp", on_extract_entry, &arg);

    return 0;
}
