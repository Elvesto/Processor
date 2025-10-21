#ifndef ASM_H_
#define ASM_H_

#include <stdio.h>

#include "../array/array.h"
#include "../processor/processor.h"

typedef struct {
    const char* nameCommand;
    Command com;
} ComInf;

typedef struct {
    const char* nameReg;
    Registers reg;
} RegInf;

static ComInf comInfo[] = {
    {.nameCommand = "PUSH",     .com = PUSH},
    {.nameCommand = "ADD",      .com = ADD},
    {.nameCommand = "SUB",      .com = SUB},
    {.nameCommand = "MUL",      .com = MUL},
    {.nameCommand = "DIV",      .com = DIV},
    {.nameCommand = "SQRT",     .com = SQRT},
    {.nameCommand = "POPR",     .com = POPR},
    {.nameCommand = "JMP",      .com = JMP},
    {.nameCommand = "JB",       .com = JB},
    {.nameCommand = "JBE",      .com = JBE},
    {.nameCommand = "JA",       .com = JA},
    {.nameCommand = "JAE",      .com = JAE},
    {.nameCommand = "JE",       .com = JE},
    {.nameCommand = "JNE",      .com = JNE},
    {.nameCommand = "IN",       .com = IN},
    {.nameCommand = "CALL",     .com = CALL},
    {.nameCommand = "RET",      .com = RET},
    {.nameCommand = "HLT",      .com = HLT},
    {.nameCommand = "OUT",      .com = OUT},
};

const int COUNT_COMMAND = sizeof(comInfo) / sizeof(comInfo[0]);

static RegInf regInfo[] = {
    {.nameReg = "RAX",          .reg = RAX},
    {.nameReg = "RBX",          .reg = RBX},
    {.nameReg = "RCX",          .reg = RCX},
    {.nameReg = "RDX",          .reg = RDX},
    {.nameReg = "REX",          .reg = REX},
    {.nameReg = "RFX",          .reg = RFX},
    {.nameReg = "RGX",          .reg = RGX},
    {.nameReg = "RESERVED",     .reg = RESERVED}
};

const int LABELS_POISON = -1;

int parser(Array* arr, char* buf);

Registers strToReg(const char* str);

Command strToCommand(const char* str);

int pushFunc(Array* arr, char* buffer);

int popFunc(Array* arr, char* buffer);

int jmpFunc(Array* arr, Array* labels, char* buffer);

int comFunc(Array* arr, char* buffer);

#endif // ASM_H_