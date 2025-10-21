#include "asm.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>

#include "../array/array.h"
#include "../instruments/colors.h"
#include "../instruments/tools.h"
#include "../processor/processor.h"

int parser(Array* arr, char* buf) {
    assert(arr);
    assert(arr->data);
    assert(buf);

    Array labels = {};
    arrayInit(&labels, 8);
    fillArray(&labels, LABELS_POISON);

    int line = 1;
    int label = 0;
    int jumps;

    int compile = 1;

    char* bufSearch = buf;
    uint64_t countCom = getCountString(buf);
    // printf("%d\n", countCom);

    for (uint64_t i = 0; i < countCom; i++) {
        //printf("%s\n", bufSearch);
        if (!bufSearch[0]) {
            fprintf(stderr, "Konec\n");
            break;
        }
        if (arr->capacity - 2 == arr->size) {
            arrayRealloc(arr);
        }
        // printf("%s\n", bufSearch);
        // printf("Number Command: %d\n", i);
        if (bufSearch[0] == ';') {
            bufSearch += strlen(bufSearch) + 1;
            // i--;
            continue;
        }
        
        if (sscanf(bufSearch, "%d:", &label)) {
            //printf("label - %d, address - %lu\n", label, i);
            if (labels.capacity <= (uint64_t)label) {
                arrayNewCap(&labels, (uint64_t)label + 1);
                fillArray(&labels, LABELS_POISON);
            }
            labels.data[label] = (int)i - jumps;;
            //arr->data[arr->size++] = LABEL;

            bufSearch += strlen(bufSearch) + 1;
            line++;
            continue;
        } 
        
        Command com = strToCommand(bufSearch);
        if (com == PUSH) {

            bufSearch += strlen(bufSearch) + 1;
            i++;

            pushFunc(arr, bufSearch);
            line++;
        } else if (com == POPR) {

            bufSearch += strlen(bufSearch) + 1;
            i++;

            popFunc(arr, bufSearch);
            line++;
        } else if (JMP <= com && com <= CALL) {
            jumps++;

            arr->data[(arr->size)++] = com;
            bufSearch += strlen(bufSearch) + 1;
            i++;

            jmpFunc(arr, &labels, bufSearch);
            line++;
        } else if (com == UNKNOWN) {

            printf("%s - %d\n", bufSearch, com);
            fprintf(stderr, RED BOLD"Unknown phrase in %d\n" RESET, line);
            arrayDestroy(&labels);

            return 1;

        } else {

            arr->data[(arr->size)++] = com;
            line++;
        }
        bufSearch += strlen(bufSearch) + 1;
        if ((compile == 1) && (i == countCom - 1)) {
            //printf("SECOND COMPILATION\n");
            compile++;
            bufSearch = buf;
            arr->size = 0;
            i = 0;
            continue;
        }
    }

    arrayDestroy(&labels);
    return 0;
}

Registers strToReg(const char* str) {
    assert(str);

    for (int i = 0; i < COUNT_REGISTERS; i++) {
        if (strcmp(regInfo[i].nameReg, str) == 0)
            return regInfo[i].reg;
    }

    return RESERVED;
}

Command strToCommand(const char* command) {
    assert(command);

    for (int i = 0; i < COUNT_COMMAND; i++) {
        if (strcmp(comInfo[i].nameCommand, command) == 0) {
            return comInfo[i].com;
        }
    }

    return UNKNOWN;
}

int pushFunc(Array* arr, char* bufSearch) {
    assert(arr);
    assert(bufSearch);

    int temp = 0;
    Registers reg = {};
    char* ptr = {};

    temp = (int)strtol(bufSearch, &ptr, 10);
    if (ptr != bufSearch) {
        arr->data[(arr->size)++] = PUSH;
        arr->data[(arr->size)++] = temp;
    } else if (ptr == bufSearch) {
        reg = strToReg(bufSearch);
        if (reg == RESERVED) return 1;
        arr->data[(arr->size)++] = PUSHR;
        arr->data[(arr->size)++] = reg;
    }

    return 0;
}

int popFunc(Array* arr, char* bufSearch) {
    assert(arr);
    assert(bufSearch);

    Registers reg = {};

    reg = strToReg(bufSearch);
    if (reg == RESERVED) return 1;
    arr->data[(arr->size)++] = POPR;
    arr->data[(arr->size)++] = reg;
    
    return 0;
}

int jmpFunc(Array* arr, Array* labels, char* bufSearch) {
    assert(arr);
    assert(labels);
    assert(bufSearch);

    uint64_t label = {};

    sscanf(bufSearch, "%lu:", &label);
    //printf("JUMP TO %d ADDRESS - %d\n", label, labels->data[label]);
    if (labels->capacity <= label) {
        labels = arrayNewCap(labels, label + 1);
        fillArray(labels, LABELS_POISON);
    }
    // printf("label - %d, jump address - %d\n", label, labels.data[label]);
    // printf("%d\n", label);
    arr->data[(arr->size)++] = labels->data[label];

    return 0;
}