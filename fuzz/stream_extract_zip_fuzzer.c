#include "zip.h"
#include <stdint.h>
#include <stdlib.h>

int on_extract_entry(const char *filename, void *arg) {
    return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, const size_t size)
{
    zip_stream_extract((char *)data, size, "/tmp", on_extract_entry, NULL);
    return 0;
}
