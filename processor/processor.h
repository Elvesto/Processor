#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "../stack/stack_t.h"
#include "../array/array.h"

typedef struct {
    Stack stack;
    Array instructions;
    size_t ip;
    int regs[8];
} Processor;

#endif // PROCESSOR