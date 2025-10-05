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
    array.capacity = 128;
    array.data = (int*)calloc(array.capacity, sizeof(int));

    
    
    while(!parser(&in, &array));

    fwrite(array.data, sizeof(int), array.size, out.file);
    
    fclose(in.file);
    fclose(out.file);

    free(array.data);

    return 0;
}