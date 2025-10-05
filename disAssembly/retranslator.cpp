#include <stdio.h>
#include <malloc.h>

#include "../array/array.h"
#include "disAsm.h"

int main(int argv, char* argc[]) {
    File bFile = {}, out = {};

    bFile.name = argc[1];
    out.name = argc[2];

    bFile.file = fopen(bFile.name, "rb");
    out.file = fopen(out.name, "w");
    if (bFile.file == NULL || out.file == NULL) {
        printf("FILE NO OPEN\n");
        return 1;
    }

    Array arr = {};
    arr.capacity = 128;
    arr.data = (int*)calloc(arr.capacity, sizeof(int));

    fread(arr.data, sizeof(int), arr.capacity - 1, bFile.file);

    disasm(&out, &arr);

    fclose(bFile.file);
    fclose(out.file);

    free(arr.data);

    return 0;
}