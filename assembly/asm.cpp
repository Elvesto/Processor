#include "asm.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../array/array.h"
#include "../instruments/colors.h"
#include "../processor/processor.h"

int parser(Array* arr, char* buf) {
    assert(arr);
    assert(arr->data);
    assert(buf);

    Array labels = {};
    arrayInit(&labels, 1);
    for (int i = 0; i < labels.capacity; i++)
        labels.data[i] = -1;

    int line = 0;
    int label = 0;

    int compile = 0;

    char* bufSearch = buf;
    size_t countCom = getCountString(buf);
    // printf("%d\n", countCom);

    for (int i = 0; i < (int)countCom; i++) {
        if (!bufSearch[0]) {
            printf("Konec\n");
            break;
        }
        if (arr->capacity - 2 == arr->size) {
            arrayRealloc(arr);
        }
        // printf("%s\n", bufSearch);
        // printf("Number Command: %d\n", i);
        if (bufSearch[0] == ';') {
            bufSearch += strlen(bufSearch) + 1;
            i--;
            continue;
        }
        
        Command com = strToCommand(bufSearch);
        if (sscanf(bufSearch, "%d:", &label) == 1) {
            // printf("label - %d, address - %d\n", label, i);
            if (labels.capacity <= label) {
                arrayNewCapacity(&labels, label + 1);
            }
            labels.data[label] = i;
            arr->data[arr->size++] = LABEL;
            // arr->data[arr->size++] = label;
            line++;
        } else if (com == PUSH) {
            line++;
            int temp = 0;

            bufSearch += strlen(bufSearch) + 1;
            i++;

            Registers reg = {};
            char* ptr;

            temp = (int)strtol(bufSearch, &ptr, 10);
            if (ptr != bufSearch) {
                arr->data[(arr->size)++] = PUSH;
                arr->data[(arr->size)++] = temp;
            } else if (ptr == bufSearch) {
                reg = strToReg(bufSearch);
                arr->data[(arr->size)++] = PUSHR;
                arr->data[(arr->size)++] = reg;
            }
            // bufSearch += strlen(bufSearch) + 1;
        } else if (com == POPR) {
            line++;

            bufSearch += strlen(bufSearch) + 1;
            i++;

            Registers reg = {};

            reg = strToReg(bufSearch);
            arr->data[(arr->size)++] = POPR;
            arr->data[(arr->size)++] = reg;
            // bufSearch += strlen(bufSearch) + 1;
        } else if (JMP <= com && com <= CALL) {
            line++;
            bufSearch += strlen(bufSearch) + 1;
            i++;

            
            sscanf(bufSearch, "%d:", &label);
            if (labels.capacity <= label) {
                arrayNewCapacity(&labels, label + 1);
            }
            // printf("label - %d, jump address - %d\n", label, labels.data[label]);
            // printf("%d\n", label);
            arr->data[(arr->size)++] = com;
            arr->data[(arr->size)++] = labels.data[label];
        } else if (com == UNKNOWN) {
            printf(RED BOLD"Unknown phrase in test.asm:%d\n" RESET, line);
            arrayDestroy(&labels);
            return 1;
        } else {
            line++; 

            arr->data[(arr->size)++] = com;
        }
        bufSearch += strlen(bufSearch) + 1;
    }

    bufSearch = buf;
    printf("SECOND CoMPILE\n");
    arr->size = 0;

    for (int i = 0; i < (int)countCom; i++) {
        if (!bufSearch[0]) {
            printf("Konec\n");
            break;
        }
        if (arr->capacity - 2 == arr->size) {
            arrayRealloc(arr);
        }
        // printf("%s\n", bufSearch);
        // printf("Number Command: %d\n", i);
        if (bufSearch[0] == ';') {
            bufSearch += strlen(bufSearch) + 1;
            continue;
        }
        
        Command com = strToCommand(bufSearch);
        if (sscanf(bufSearch, "%d:", &label) == 1) {

            if (labels.capacity <= label) {
                arrayNewCapacity(&labels, label + 1);
            }
            // printf("label - %d, address - %d\n", label, i);
            labels.data[label] = i;
            arr->data[arr->size++] = LABEL;
            // arr->data[arr->size++] = label;
            line++;
        } else if (com == PUSH) {
            line++;
            int temp = 0;

            bufSearch += strlen(bufSearch) + 1;
            i++;

            Registers reg = {};
            char* ptr;

            temp = (int)strtol(bufSearch, &ptr, 10);
            if (ptr != bufSearch) {
                arr->data[(arr->size)++] = PUSH;
                arr->data[(arr->size)++] = temp;
            } else if (ptr == bufSearch) {
                reg = strToReg(bufSearch);
                arr->data[(arr->size)++] = PUSHR;
                arr->data[(arr->size)++] = reg;
            }
            // bufSearch += strlen(bufSearch) + 1;
        } else if (com == POPR) {
            line++;

            bufSearch += strlen(bufSearch) + 1;
            i++;

            Registers reg = {};

            reg = strToReg(bufSearch);
            arr->data[(arr->size)++] = POPR;
            arr->data[(arr->size)++] = reg;
            // bufSearch += strlen(bufSearch) + 1;
        } else if (JMP <= com && com <= CALL) {
            line++;
            bufSearch += strlen(bufSearch) + 1;
            i++;

            
            sscanf(bufSearch, "%d:", &label);
            if (labels.capacity <= label) {
                arrayNewCapacity(&labels, label + 1);
            }
            // printf("label - %d, jump address - %d\n", label, labels.data[label]);
            // printf("%d\n", label);
            arr->data[(arr->size)++] = com;
            arr->data[(arr->size)++] = labels.data[label];
        } else if (com == UNKNOWN) {
            printf(RED BOLD"Unknown phrase in test.asm:%d\n" RESET, line);
            arrayDestroy(&labels);
            return 1;
        } else {
            line++; 

            arr->data[(arr->size)++] = com;
        }
        bufSearch += strlen(bufSearch) + 1;
    }

    arrayDestroy(&labels);
    return 0;
}

Registers strToReg(const char* str) {
    Registers reg = {};
    if (strcmp(str, "RAX") == 0) {
        reg = RAX;
    } else if (strcmp(str, "RBX") == 0) {
        reg = RBX;
    } else if (strcmp(str, "RCX") == 0) {
        reg = RCX;
    } else if (strcmp(str, "RDX") == 0) {
        reg = RDX;
    } else if (strcmp(str, "REX") == 0) {
        reg = REX;
    } else if (strcmp(str, "RFX") == 0) {
        reg = RFX;
    } else if (strcmp(str, "RGX") == 0) {
        reg = RGX;
    }

    return reg;
}

Command strToCommand(const char* command) {
    if ((strcmp(command, "PUSH") == 0) || (strcmp(command, "TOLKAI") == 0))
        return PUSH;
    else if ((strcmp(command, "ADD") == 0) || (strcmp(command, "DOBAV") == 0))
        return ADD;
    else if ((strcmp(command, "SUB") == 0) || (strcmp(command, "HUAR") == 0))
        return SUB;
    else if ((strcmp(command, "OUT") == 0) || (strcmp(command, "EBI") == 0))
        return OUT;
    else if ((strcmp(command, "HLT") == 0) || (strcmp(command, "POK") == 0))
        return HLT;
    else if ((strcmp(command, "MUL") == 0) || (strcmp(command, "EBASH") == 0))
        return MUL;
    else if ((strcmp(command, "DIV") == 0) || (strcmp(command, "DELI") == 0))
        return DIV;
    else if ((strcmp(command, "SQRT") == 0) || (strcmp(command, "SQVIRT") == 0))
        return SQRT;
    else if ((strcmp(command, "POPR") == 0) || (strcmp(command, "POP") == 0))
        return POPR;
    else if ((strcmp(command, "JMP") == 0))
        return JMP;
    else if ((strcmp(command, "JB") == 0))
        return JB;
    else if ((strcmp(command, "JBE") == 0))
        return JBE;
    else if ((strcmp(command, "JA") == 0))
        return JA;
    else if ((strcmp(command, "JAE") == 0))
        return JAE;
    else if ((strcmp(command, "JE") == 0))
        return JE;
    else if ((strcmp(command, "JNE") == 0))
        return JNE;
    else if ((strcmp(command, "IN") == 0))
        return IN;
    else if ((strcmp(command, "CALL") == 0))
        return CALL;
    else if ((strcmp(command, "RET") == 0))
        return RET;
    else {
        return UNKNOWN;
    }
}

int bufCreate(char** text, File* file) {
    struct stat info;

    if (fstat(fileno(file->file), &info) != 0) {
        return -1;
    }

    *text = (char*)calloc((size_t)(info.st_size + 1), sizeof(char));

    fread(*text, sizeof(char), (size_t)info.st_size, file->file);

    (*text)[info.st_size] = '\0';
    // printf("%s\n", *text);

    return 0;
}

size_t getCountString(char* buf) {
    assert(buf != NULL);
    size_t res = 0;
    char* ptr = buf;
    for (; (ptr = strchr(ptr, '\n')) != NULL; ) {
        *ptr = ' ';
        ptr++;
    }
    ptr = buf;
    for (res = 0; (ptr = strchr(ptr, ' ')) != NULL; res++) {
        *ptr = '\0';
        ptr++;
    }
    return res;
}

int nonEmptyCells(Array* arr, int defaultValue) {
    assert(arr);
    int res = 0;
    for (int i = 0; i < arr->capacity; i++) {
        res = arr->data[i] != defaultValue ? res + 1 : res;
    }

    return 0;
}