#include "tools.h"

#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int equal(double num1, double num2) {
    return fabs(num1 - num2) < EPS;
}

uint64_t sizeFile(FILE* file) {
    assert(file);

    struct stat info;
    if (fstat(fileno(file), &info) != 0) {
        fprintf(stderr, "CHTO-TO POSHLO NE TAK\n");
        return 0;
    }

    return (uint64_t)info.st_size;
}

char* bufCreate(FileParam* file) {
    assert(file);

    uint64_t fsize = sizeFile(file->file);

    char* buffer = (char*)calloc(fsize + 1, sizeof(char));

    fread(buffer, sizeof(char), fsize, file->file);

    buffer[fsize] = '\0';
    // printf("%s\n", *text);

    return buffer;
}

size_t getCountString(char* buf) {
    assert(buf != NULL);
    
    size_t res = 0;
    char* ptr = buf;
    for (; (ptr = strchr(ptr, '\n')) != NULL; ) {
        *ptr = ' ';
        ptr++;
    }
    ptr = buf;
    for (res = 0; (ptr = strchr(ptr, ' ')) != NULL; res++) {
        *ptr = '\0';
        ptr++;
    }
    return res;
}