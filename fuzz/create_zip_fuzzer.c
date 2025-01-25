#include "zip.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, const size_t size)
{
    char *outbuf = NULL;
    size_t outbufsize = 0;

    struct zip_t *zip = zip_stream_open(NULL, 0, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');

    zip_entry_open(zip, "test");
    zip_entry_write(zip, data, size);
    zip_entry_close(zip);
    zip_stream_copy(zip, (void **) &outbuf, &outbufsize);
    zip_stream_close(zip);
    free(outbuf);

    char* temp_name = tmpnam(NULL);
    FILE* file = fopen(temp_name, "wb");
    fwrite(data, size, 1, file);
    fclose(file);

    const char *filenames[] = {temp_name};
    zip_create("/tmp/test.zip", filenames, 1);

    return 0;
}
