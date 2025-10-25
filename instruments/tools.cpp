#include "tools.h"

#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

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

    return (uint64_t)info.st_size + 1;
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

size_t getCountString(char *buf) {
    assert(buf != NULL);

    size_t count = 0;
    int inWord = 0;

    for (char* ptr = buf; *ptr; ptr++) {
        if (*ptr == '\n') {
            *ptr = '\0';
            inWord = 0;
            continue;
        }

        if (isspace(*ptr)) {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            count++;
        }
    }

    return count;
}