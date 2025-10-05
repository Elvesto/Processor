#include <stdio.h>
#include <malloc.h>

#include "../array/array.h"
#include "asm.h"

int main(int argv, char* argc[]) {
    File in = {}, out = {}, dis = {};
    in.name = argc[1];
    out.name = argc[2];
    dis.name = argc[3];

    in.file = fopen(in.name, "r");
    out.file = fopen(out.name, "wb");
    dis.file = fopen(dis.name, "w");
    if (in.file == NULL || out.file == NULL || dis.file == NULL) {
        printf("FILE NO OPEN\n");
        return 1;
    }

    Array array = {};
    array.capacity = 128;
    array.data = (int*)calloc(array.capacity, sizeof(int));

    
    
    while(!parser(&in, &array));

    fwrite(array.data, sizeof(int), array.size, out.file);

    disasm(&dis, &array);
    
    fclose(in.file);
    fclose(out.file);

    free(array.data);

    return 0;
}