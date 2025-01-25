#include "zip.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


int LLVMFuzzerTestOneInput(const uint8_t *data, const size_t size)
{
    char* temp_name = tmpnam(NULL);
    struct zip_t *zip = zip_open(temp_name, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    zip_entry_open(zip, "test_file.txt");
    zip_entry_write(zip, data, size);
    zip_entry_close(zip);
    char *entries[] = {"test_file_not_there.txt", "test_file.txt"};
    zip_entries_delete(zip, entries, 2);
    zip_close(zip);

    return 0;
}
