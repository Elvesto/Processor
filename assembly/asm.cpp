#include "asm.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>

#include "../array/array.h"
#include "colors.h"

int parser(File* in, Array* arr) {
    assert(in);
    assert(arr);
    assert(arr->data);
    if (arr->capacity == arr->size) {
        int* temp = (int*)realloc(arr->data, arr->capacity * 2);
        if (!temp) {
            return 1;
        }
        arr->data = temp;
        assert(arr->data);
    }
    char command[10] = {};
    static unsigned int line = 1;

    fscanf(in->file, "%9s", command);

    if ((strcmp(command, "PUSH") == 0) || (strcmp(command, "TOLKAI") == 0)) {
        int temp = 0;
        fscanf(in->file, "%d", &temp);
        arr->data[(arr->size)++] = PUSH;
        arr->data[(arr->size)++] = temp;
    } else if ((strcmp(command, "ADD") == 0) || (strcmp(command, "DOBAV") == 0)) {
        arr->data[(arr->size)++] = ADD;
    } else if ((strcmp(command, "SUB") == 0) || (strcmp(command, "HUAR") == 0)) {
        arr->data[(arr->size)++] = SUB;
    } else if ((strcmp(command, "OUT") == 0) || (strcmp(command, "EBI") == 0)) {
        arr->data[(arr->size)++] = OUT;
    } else if ((strcmp(command, "HLT") == 0) || (strcmp(command, "POK") == 0)) {
        arr->data[(arr->size)++] = HLT;
        return 1;
    } else if ((strcmp(command, "MUL") == 0) || (strcmp(command, "EBASH") == 0)) {
        arr->data[(arr->size)++] = MUL;
    } else if ((strcmp(command, "DIV") == 0) || (strcmp(command, "DELI") == 0)) {
        arr->data[(arr->size)++] = DIV;
    } else if ((strcmp(command, "SQRT") == 0) || (strcmp(command, "SQVRT") == 0)) {
        arr->data[(arr->size)++] = SQRT;
    } else if (strchr(command, ';')) {
        *(strchr(command, ';')) = '\0';
    } else {
        printf(RED BOLD"Unknown phrase in %s:%u\n" RESET, in->name, line);
        return 1;
    }

    line++;

    return 0;
}

int disasm(File* out, Array* arr) {
    for (int i = 0; ; i++) {
        switch (arr->data[i]) {
            case PUSH: 
            {
                fprintf(out->file, "PUSH %d\n", arr->data[++i]);
                break;
            }
            case ADD:
            {
                fprintf(out->file, "ADD\n");
                break;
            }
            case SUB:
            {
                fprintf(out->file, "SUB\n");
                break;
            }
            case MUL:
            {
                fprintf(out->file, "MUL\n");
                break;
            }
            case DIV:
            {
                fprintf(out->file, "DIV\n");
                break;
            }
            case SQRT:
            {
                fprintf(out->file, "SQRT\n");
                break;
            }
            case OUT:
            {
                fprintf(out->file, "OUT\n");
                break;
            }
            case HLT:
            {
                fprintf(out->file, "HLT\n");
                return 1;
            }
            default:
            {
                printf("razrab daun\n");
            }
        }
    }
    return 0;
}