#include "zip.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int on_extract_entry(const char *filename, void *arg) {
    return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, const size_t size)
{
    char* temp_name = tmpnam(NULL);
    FILE* file = fopen(temp_name, "wb");
    fwrite(data, size, 1, file);
    fclose(file);

    zip_extract(temp_name, "/tmp", on_extract_entry, NULL);
    unlink(temp_name);

    return 0;
}
