#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "../stack/stack_t.h"
#include "../array/array.h"


enum Registers {
    RESERVED = 0,
    RAX = 1,
    RBX = 2,
    RCX = 3,
    RDX = 4,
    REX = 5,
    RFX = 6,
    RGX = 7
};

typedef struct {
    Stack stack;
    Array instructions;
    int64_t ip;
    int regs[8];
    Stack returnAddress;
} Processor;

enum ProcessorErrors {
    NO_PROBLEMS = 0,
    STACK_ERROR = 1,
    INIT_ERROR = 2,
    DESTROY_ERROR = 3,
    FILE_ERROR = 4,
    STRANGE = 5,
    NULL_POINTER = 6,

    //  . .
};

ProcessorErrors procInit(Processor* proc);

ProcessorErrors procDestroy(Processor* proc);

//TODO



#endif // PROCESSOR_H_