#include <stdio.h>
#include <stdlib.h>

char* getFileString(const char* path) {
    printf("hello from testing\n");
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s", path);
    }

    // Make buffer large enough to hold file
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = malloc(fsize + 1);
    // Read file into buffer
    fread(buffer, fsize, 1, file);
    printf("buffer is: %s\n", buffer);
    return buffer;
};