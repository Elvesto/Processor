#include "asm.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>

#include "../array/array.h"
#include "../instruments/colors.h"
#include "../processor/processor.h"

int parser(File* in, Array* arr) {
    assert(in);
    assert(arr);
    assert(arr->data);

    if (arr->capacity == arr->size) {
        arrayRealloc(arr);
    }

    char command[10] = {};
    static unsigned int line = 1;
    int label = 0;

    fscanf(in->file, "%9s", command);

    Command com = strToCommand(command);
    if (sscanf(command, "%d:", &label) == 1) {
        arr->data[(arr->size)++] = LABEL;
        arr->data[(arr->size)++] = label;
    } else if (com == PUSH) {
        long long temp = 0;
        char str[32] = {};
        char* ptr;
        Registers reg = {};

        fscanf(in->file, "%31s", str);

        temp = strtol(str, &ptr, 10);
        if (ptr != str && temp != LONG_MAX && temp != LONG_MIN) {
            arr->data[(arr->size)++] = PUSH;
            arr->data[(arr->size)++] = (int)temp;
        } else if (ptr == str) {
            reg = strToReg(str);
            arr->data[(arr->size)++] = PUSHR;
            arr->data[(arr->size)++] = reg;
        }
    } else if (com == POPR) {
        char str[10] = {};
        Registers reg = {};

        fscanf(in->file, "%9s", str);
        reg = strToReg(str);

        arr->data[(arr->size)++] = POPR;
        arr->data[(arr->size)++] = reg;
    } else if (JMP <= com && com <= CALL) {
        // int label = 0;
        fscanf(in->file, "%d:", &label);
        arr->data[(arr->size)++] = com;
        arr->data[(arr->size)++] = label;
    } else if (com == UNKNOWN) {
        printf(RED BOLD"Unknown phrase in %s:%u\n" RESET, in->name, line);
        return 1;
    } else if (com == HLT) {
        return 2;
    } else {
        arr->data[(arr->size)++] = com;
    }

    line++;

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