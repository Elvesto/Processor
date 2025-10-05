#include <stdio.h>

#include <assert.h>
#include <malloc.h>

#include "../logs/log.h"
#include "calc.h"
#include "processor.h"

int main() {
    openLog("../files/dumps.txt");
    
    Processor processor = {};
    StackError err = OK;

    err = stackInit(&processor.stack, 30);
    if (err) {
        perror("TEXT_CREATE_ERROR");
        return err;
    }

    processor.instructions.capacity = 128;
    processor.instructions.data = (int*)calloc(processor.instructions.capacity, sizeof(int));
    if (processor.instructions.data == NULL) {
        printf("No memory allocotaion\n");
        return PTR_ERROR;
    }

    FILE* byteCode = fopen("../files/byteCode.bin", "rb");
    if (fread(processor.instructions.data, sizeof(int), processor.instructions.capacity - 1, byteCode) != 128) {
        if (feof(byteCode) == 0) {
            printf("File no open\n");
            return PTR_ERROR;
        }
    }

    // for (int i = 0; i < instructions.capacity; i++)
    //     printf("%d\n", instructions.data[i]);

    err = executor(&processor);
    if (err) {
        perror(errorToString(err));
        return err;
    }

    err = stackDestroy(&processor.stack);
    if (err) {
        perror(errorToString(err));
        return PTR_ERROR;
    }
        

    fclose(byteCode);
    
    free(processor.instructions.data);
    
    closeLog();
}