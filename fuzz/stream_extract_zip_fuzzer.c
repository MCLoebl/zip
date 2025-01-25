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
    size_t zipstreamsize;
    struct zip_t *zip = zip_stream_open(NULL, zipstreamsize, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    zip_entry_open(zip, "test");
    zip_entry_write(zip, data, size);
    zip_entry_close(zip);
    int arg = 2;
    zip_stream_extract(zip, zipstreamsize, "/tmp", on_extract_entry, &arg);
    zip_stream_close(zip);

    return 0;
}
