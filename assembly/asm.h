#ifndef ASM_H_
#define ASM_H_

#include <stdio.h>

#include "../array/array.h"
#include "../processor/processor.h"

enum Command {
    HLT =  0,
    PUSH =  1,
    ADD  =  2,
    SUB  =  3,
    MUL  =  4,
    DIV  =  5,
    SQRT =  6,
    OUT  =  7,
    PUSHR = 42,
    POPR = 33,
    IN = 10,
    JMP = 20,
    JB = 21,
    JBE = 22,
    JA = 23,
    JAE = 24,
    JE = 25,
    JNE = 26,
    CALL = 27, 
    RET = 28,
    LABEL = 30,
    UNKNOWN = -1,
};

typedef struct {
    char* name;
    FILE* file;
} File;

int parser(File* in, Array* arr);

Registers strToReg(const char* str);

Command strToCommand(const char* str);

#endif //ASM_H_