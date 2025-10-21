#include <stdio.h>

#include <assert.h>
#include <malloc.h>

#include "../logs/log.h"
#include "calc.h"
#include "processor.h"

// ХУЙНЯ ПЕРЕДЕЛЫВАЙ
// Дамп процессора +-
// Процессор верифи +-
// Обработка ошибок -
// Решить квадратку +-
// RAM, VRAM -
int main() {
    openLog("../files/dumps.txt");
    
    Processor processor = {};
    ProcessorErrors err = NO_PROBLEMS;

    FILE* byteCode = fopen("../files/byteCode.bin", "rb");

    err = procInit(&processor, byteCode);
    if (err) {
        printf("Processor not initialisated\n");
        return err;
    }

    if (fread(processor.instructions.data, sizeof(int), processor.instructions.capacity - 1, byteCode) != processor.instructions.capacity - 1) {
        if (!feof(byteCode)) {
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