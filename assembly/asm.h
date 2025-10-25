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
    uint64_t index;
    int label;
} LabelInfo;

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
    {.nameCommand = "POP",      .com = POPR},
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
    {.nameCommand = "DRAW",     .com = DRAW},
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

int pushFunction(Array* arr, char* buffer);

int popFunction(Array* arr, char* buffer);

int jmpFunction(Array* arr, Array* labels, char* buffer, Array* labelsCompile);

// int comFunction(Array* arr, char* buffer);

// int compileAsm(uint64_t countCom, char* bufIter, Array* labels, Array* arr, );

#endif // ASM_H_