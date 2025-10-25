#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "../stack/stack_t.h"
#include "../array/array.h"

#define PROC_DUMP(proc) procDump(proc, __FILE__, __FUNCTION__, __LINE__);

const int COUNT_REGISTERS = 8;
const int RAM_SIZE = 100;

typedef enum {
    HLT =  0,
    PUSH =  1,
    ADD  =  2,
    SUB  =  3,
    MUL  =  4,
    DIV  =  5,
    SQRT =  6,
    OUT  =  7,
    PUSHR = 8,
    POPR = 9,
    IN = 10,
    JMP = 11,
    JB = 12,
    JBE = 13,
    JA = 14,
    JAE = 15,
    JE = 16,
    JNE = 17,
    CALL = 18, 
    RET = 19,
    LABEL = 20,
    PUSHM = 21,
    POPM = 22,
    DRAW = 23,
    UNKNOWN = -1,
    
} Command;

typedef enum Registers {
    RESERVED = 0,
    RAX = 1,
    RBX = 2,
    RCX = 3,
    RDX = 4,
    REX = 5,
    RFX = 6,
    RGX = 7
} Registers;

typedef struct {
    Stack stack;
    Array instructions;
    int64_t ip;
    int regs[COUNT_REGISTERS];
    Stack returnAddress;
    Array ram;
} Processor;

enum ProcessorErrors {
    NO_PROBLEMS = 0,
    STACK_ERROR = 1,
    INIT_ERROR = 2,
    DESTROY_ERROR = 3,
    FILE_ERROR = 4,
    STRANGE = 5,
    NULL_POINTER = 6,
    POINTER_ERROR = 7,
    EXIT = 8,
    
    //  . .
};

ProcessorErrors procInit(Processor* proc, FILE* byteCode);

ProcessorErrors procDestroy(Processor* proc);

ProcessorErrors procVerify(Processor* proc);

int procDump(Processor* proc, const char* f, const char* func, int line);

ProcessorErrors draw(Processor* proc);

#endif // PROCESSOR_H_