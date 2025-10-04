#ifndef CALC_H_
#define CALC_H_

#include "stack/stack_t.h"
#include "processor/processor.h"

typedef enum {
    HLT =  0,
    PUSH =  1,
    ADD  =  2,
    SUB  =  3,
    MUL  =  4,
    DIV  =  5,
    SQRT =  6,
    OUT  =  7
} Command;

StackError executor(Processor* proc);

#endif // CALC_H_