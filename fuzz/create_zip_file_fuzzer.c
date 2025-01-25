#include "zip.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int on_extract_entry(const char *filename, void *arg) {
    static int i = 0;
    int n = *(int *)arg;
    printf("Extracted: %s (%d of %d)\n", filename, ++i, n);
    return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, const size_t size)
{
    char* temp_name = tmpnam(NULL);
    struct zip_t *zip = zip_open(temp_name, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    zip_entry_open(zip, "test_file.txt");
    zip_entry_write(zip, data, size);
    zip_entry_close(zip);
    zip_close(zip);

    int arg = 2;
    zip_extract(temp_name, "/tmp", on_extract_entry, &arg);

    return 0;
}
