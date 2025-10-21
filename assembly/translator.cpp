#include <stdio.h>
#include <malloc.h>

#include "../instruments/tools.h"
#include "../array/array.h"
#include "asm.h"

int main(int argv, char* argc[]) {
    FileParam in = {}, out = {};
    if (argv == 3) {
        in.name = argc[1];
        out.name = argc[2];
    } else {
        fprintf(stderr, "Incorrect param\n");
        return 1;
    }

    in.file = fopen(in.name, "r");
    out.file = fopen(out.name, "wb");
    if (in.file == NULL || out.file == NULL) {
        fprintf(stderr, "FILE NO OPEN\n");
        return 1;
    }

    Array array = {};
    arrayInit(&array, 128);
    
    char* buf = {};

    buf = bufCreate(&in);

    parser(&array, buf);

    for (uint64_t i = 0; i < array.capacity; i++)
        printf("%d\n", array.data[i]);

    fwrite(array.data, sizeof(int), array.size, out.file);
    
    fclose(in.file);
    fclose(out.file);

    arrayDestroy(&array);

    free(buf);

    return 0;
}