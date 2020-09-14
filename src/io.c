#include "include/io.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Reads and returns blink source file.
 * 
 * @param[in] filepath String of path to source file.
 * @return buffer Returns read characters of blink 
 *         source file. Otherwise, the program will print an error and exit.
 */
char* get_file_contents(const char* filepath) {
    char* buffer = 0;
    long length;

    FILE* f = fopen(filepath, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        buffer = calloc(length, length);

        if (buffer)
            fread(buffer, 1, length, f);

        fclose(f);
        return buffer;
    }

    printf("Error reading file %s\n", filepath);
    exit(2);
}
