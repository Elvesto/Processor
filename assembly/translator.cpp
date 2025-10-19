#include <stdio.h>
#include <malloc.h>

#include "../array/array.h"
#include "asm.h"

int main(int argv, char* argc[]) {
    File in = {}, out = {};
    in.name = argc[1];
    out.name = argc[2];

    in.file = fopen(in.name, "r");
    out.file = fopen(out.name, "wb");
    if (in.file == NULL || out.file == NULL) {
        printf("FILE NO OPEN\n");
        return 1;
    }

    Array array = {};
    arrayInit(&array, 128);
    
    char* buf = {};

    bufCreate(&buf, &in);

    parser(&array, buf);

    // for (int i = 0; i < array.capacity; i++)
    //     printf("%d\n", array.data[i]);

    fwrite(array.data, sizeof(int), array.size, out.file);
    
    fclose(in.file);
    fclose(out.file);

    free(array.data);
    free(buf);

    return 0;
}