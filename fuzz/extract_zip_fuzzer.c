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
    FILE* file = fopen(temp_name, "wb");
    fwrite(data, size, 1, file);
    fclose(file);

    int arg = 2;
    zip_extract(temp_name, "/tmp", on_extract_entry, &arg);

    return 0;
}
