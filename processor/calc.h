#ifndef CALC_H_
#define CALC_H_

#include "../stack/stack_t.h"
#include "processor.h"

#define OPERATION(a) \
int temp1 = 0, temp2 = 0; \
temp2 = stackPop(stack, &err); \
temp1 = stackPop(stack, &err); \
err = stackPush(stack, temp1 a temp2)

#define JUMP_IF(a) \
int temp = instructions->data[++(proc->ip)]; \
int el2 = stackPop(stack, &err); \
int el1 = stackPop(stack, &err); \
if (el1 a el2) \
    proc->ip = temp
    

typedef enum {
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
    
} Command;

ProcessorErrors executor(Processor* proc);



#endif // CALC_H_