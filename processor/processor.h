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
    size_t ip;
    int regs[8];
} Processor;

#endif // PROCESSOR