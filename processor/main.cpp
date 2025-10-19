#include <stdio.h>

#include <assert.h>
#include <malloc.h>

#include "../logs/log.h"
#include "calc.h"
#include "processor.h"

//ХУЙНЯ ПЕРЕДЕЛЫВАЙ
// Дамп процессора +-
// Процессор верифи +-
// Обработка ошибок -
// Решить квадратку +-
// RAM, VRAM -
int main() {
    openLog("../files/dumps.txt");
    
    Processor processor = {};
    ProcessorErrors err = NO_PROBLEMS;

    // err = stackInit(&processor.stack, 30);
    // if (err) {
    //     perror("TEXT_CREATE_ERROR");
    //     return err;
    // }

    // processor.instructions.capacity = 128;
    // processor.instructions.data = (int*)calloc(processor.instructions.capacity, sizeof(int));
    // if (processor.instructions.data == NULL) {
    //     printf("No memory allocotaion\n");
    //     return PTR_ERROR;
    // }

    err = procInit(&processor);
    if (err) {
        printf("Processor not initialisated\n");
        return err;
    }

    FILE* byteCode = fopen("../files/byteCode.bin", "rb");
    if (fread(processor.instructions.data, sizeof(int), processor.instructions.capacity - 1, byteCode) != 128) {
        if (feof(byteCode) == 0) {
            printf("File no open\n");
            return FILE_ERROR;
        }
    }

    // for (int i = 0; i < processor.instructions.capacity; i++)
    //     printf("%d\n", processor.instructions.data[i]);

    err = executor(&processor);
    if (err) {
        printf("%d\n", err);
        return err;
    }

    err = procDestroy(&processor);
    if (err) {
        printf("error2\n");
        return err;
    }
        

    fclose(byteCode);
    
    closeLog();
}