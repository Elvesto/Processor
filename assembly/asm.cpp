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

    Array labelsCompile = {};
    arrayInit(&labelsCompile, labels.capacity * 2);

    int line = 1;
    int label = 0;
    int jumps = 0;
    // int compile = 1;

    char* bufIter = buf;
    uint64_t countCom = getCountString(buf);

    for (uint64_t i = 0; i < countCom; i++) {
        if (!*bufIter) {
            break;
        }

        size_t lenStr = strlen(bufIter);
        char* firstParam = strtok(bufIter, " ;");
        char* secondParam = strtok(NULL, " ;");
        // printf("%s %s\n", firstParam, secondParam);

        if (!firstParam[0]) {
            fprintf(stderr, "Empty line at %d\n", line);
        }

        if (arr->capacity - 2 == arr->size) {
            arrayRealloc(arr);
        }

        if (sscanf(firstParam, "%d:", &label) == 1) {
            if (labels.capacity <= (uint64_t)label) {
                arrayNewCap(&labels, (uint64_t)label + 1);
                fillArray(&labels, LABELS_POISON);
            }
            labels.data[label] = (int)i - jumps;
            bufIter += lenStr + 1;
            line++;
            continue;
        }

        Command com = strToCommand(firstParam);

        if (com == PUSH) {
            if (secondParam == NULL) {
                fprintf(stderr, RED BOLD "Missing argument for PUSH at line %ld\n" RESET, i);
                arrayDestroy(&labels);
                return 1;
            }

            pushFunction(arr, secondParam);
            i++;
        } else if (com == POPR) {
            if (secondParam == NULL) {
                fprintf(stderr, RED BOLD "Missing argument for POP at line %d %s %s\n" RESET, i, firstParam, secondParam);
                arrayDestroy(&labels);
                return 1;
            }

            popFunction(arr, secondParam);
            i++;
        } else if (JMP <= com && com <= CALL) {
            jumps++;
            arr->data[arr->size++] = com;
            jmpFunction(arr, &labels, secondParam, &labelsCompile);
            i++;
        } else if (com == UNKNOWN) {
            fprintf(stderr, RED BOLD "Unknown phrase at line %d: %s %s\n" RESET,
                    line, firstParam, secondParam ? secondParam : "");
            arrayDestroy(&labels);
            return 1;
        } else {
            arr->data[arr->size++] = com;
        }

        bufIter += lenStr + 1;
        line++;
    }

    for (uint64_t i = 0; i < labelsCompile.size; i++) {
        arr->data[labelsCompile.data[i]] = labels.data[labelsCompile.data[i + 1]];
        i++;
    }

    arrayDestroy(&labels);
    arrayDestroy(&labelsCompile);
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

int pushFunction(Array* arr, char* bufSearch) {
    assert(arr);
    assert(bufSearch);

    int temp = 0;
    Registers reg = {};
    char* ptr = {};
    if ((ptr = strchr(bufSearch, ' ')) != NULL) {
        *ptr = '\0';
    }

    temp = (int)strtol(bufSearch, &ptr, 10);
    if (ptr != bufSearch) {
        arr->data[(arr->size)++] = PUSH;
        arr->data[(arr->size)++] = temp;
    } else if (ptr == bufSearch) {
        char regStr[8] = "";
        if (sscanf(bufSearch, "[%3s]", regStr) == 1) {
            reg = strToReg(regStr);
            // if (reg == RESERVED) return 1;
            arr->data[(arr->size)++] = PUSHM;
            // arr->data[(arr->size)++] = reg;
            // return 0;
        } else {
            reg = strToReg(bufSearch);
            arr->data[(arr->size)++] = PUSHR;
        }
        if (reg == RESERVED) return 1;
        arr->data[(arr->size)++] = reg;
    }

    return 0;
}

int popFunction(Array* arr, char* bufSearch) {
    assert(arr);
    assert(bufSearch);

    
    Registers reg = {};
    char* ptr = {};
    if ((ptr = strchr(bufSearch, ' ')) != NULL) {
        *ptr = '\0';
    }
    
    char regStr[8] = "";
    if (sscanf(bufSearch, "[%3s]", regStr)) {
        reg = strToReg(regStr);
        arr->data[(arr->size)++] = POPM;
        // if (reg == RESERVED) return 1;
        // arr->data[(arr->size)++] = reg;
    }
    else {
        reg = strToReg(bufSearch);
        // printf("GOOOOOOOL --- %d\n", reg);
        arr->data[(arr->size)++] = POPR;
    }
    if (reg == RESERVED) return 1;
    arr->data[(arr->size)++] = reg;
    
    return 0;
}

int jmpFunction(Array* arr, Array* labels, char* bufSearch, Array* labelsCompile) {
    assert(arr);
    assert(labels);
    assert(bufSearch);

    uint64_t label = {};
    char* ptr = {};
    if ((ptr = strchr(bufSearch, ' ')) != NULL) {
        *ptr = '\0';
    }

    sscanf(bufSearch, "%lu:", &label);
    //printf("JUMP TO %d ADDRESS - %d\n", label, labels->data[label]);
    if (labels->capacity <= label) {
        labels = arrayNewCap(labels, label + 1);
        fillArray(labels, LABELS_POISON);
    }
    // printf("label - %d, jump address - %d\n", label, labels.data[label]);
    // printf("%d\n", label);
    if (labels->data[label] != LABELS_POISON) {
        arr->data[(arr->size)++] = labels->data[label];
    } else {
        if (labelsCompile->size + 2 >= labelsCompile->capacity) {
            arrayRealloc(labelsCompile);
        }
        arr->data[(arr->size)++] = labels->data[label];
        labelsCompile->data[labelsCompile->size++] = (int)arr->size - 1;
        labelsCompile->data[labelsCompile->size++] = (int)label;
    }

    return 0;
}