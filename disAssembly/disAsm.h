#ifndef DISASM_H_
#define DISASM_H_

#include <stdio.h>

#include "../array/array.h"

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
    POPR = 32,
    IN = 10,
};

typedef struct {
    char* name;
    FILE* file;
} File;


int disasm(File* out, Array* arr);

#endif // DISASM_H_