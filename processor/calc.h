#ifndef CALC_H_
#define CALC_H_

#include "../stack/stack_t.h"
#include "processor.h"

typedef ProcessorErrors (*action)(Processor* proc);

#define OPERATION(a) \
int temp1 = 0, temp2 = 0; \
temp2 = stackPop(stack, &err); \
temp1 = stackPop(stack, &err); \
err = stackPush(stack, temp1 a temp2)

#define JUMP_IF(a) \
int temp = proc->instructions.data[++(proc->ip)]; \
int el2 = stackPop(stack, &err); \
int el1 = stackPop(stack, &err); \
if (el1 a el2) \
    proc->ip = temp

typedef struct {
    Command com;
    action func;
} ExecuteCommand;

ProcessorErrors executor(Processor* proc);

ProcessorErrors hltFunc(Processor* proc);

ProcessorErrors pushFunc(Processor* proc);

ProcessorErrors opFunc(Processor* proc);

ProcessorErrors sqrtFunc(Processor* proc);

ProcessorErrors outFunc(Processor* proc);

ProcessorErrors pushRFunc(Processor* proc);

ProcessorErrors popRFunc(Processor* proc);

ProcessorErrors inFunc(Processor* proc);

ProcessorErrors jmpFunc(Processor* proc);

ProcessorErrors nothing(Processor* proc);

static ExecuteCommand execute[] = {
    {.com = HLT, .func = hltFunc},
    {.com = PUSH, .func = pushFunc},
    {.com = ADD, .func = opFunc},
    {.com = SUB, .func = opFunc},
    {.com = MUL, .func = opFunc},
    {.com = DIV, .func = opFunc},
    {.com = SQRT, .func = sqrtFunc},
    {.com = OUT, .func = outFunc},
    {.com = PUSHR, .func = pushRFunc},
    {.com = POPR, .func = popRFunc},
    {.com = IN, .func = inFunc},
    {.com = JMP, .func = jmpFunc},
    {.com = JB, .func = jmpFunc},
    {.com = JBE, .func = jmpFunc},
    {.com = JA, .func = jmpFunc},
    {.com = JAE, .func = jmpFunc},
    {.com = JE, .func = jmpFunc},
    {.com = JNE, .func = jmpFunc},
    {.com = CALL, .func = jmpFunc},
    {.com = RET, .func = jmpFunc},
    {.com = LABEL, .func = nothing},
};

#endif // CALC_H_