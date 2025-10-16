#include "processor.h"

#include <string.h>

#include "../stack/stack_t.h"
#include "../array/array.h"

ProcessorErrors procInit(Processor* proc) {
    if (!proc) {
        return INIT_ERROR;
    }

    stackInit(&(proc->stack), 14);
    stackInit(&(proc->returnAddress), 14);

    arrayInit(&(proc->instructions), 128);

    proc->ip = 0;

    for (int i = 0; i < proc->instructions.capacity; i++) {
        proc->instructions.data[i] = 0;
    }

    for (int i = 0; i < 8; i++) {
        proc->regs[i] = 0;
    }

    return NO_PROBLEMS;
}

ProcessorErrors procDestroy(Processor* proc) {
    if (!proc) {
        return DESTROY_ERROR;
    }
    
    StackError err = stackDestroy(&(proc->stack));
    if (err) {
        return STACK_ERROR;
    }
    err = stackDestroy(&(proc->returnAddress));
    if (err) {
        return STACK_ERROR;
    }

    arrayDestroy(&(proc->instructions));

    proc->ip = 0;

    for (int i = 0; i < 8; i++) {
        proc->regs[i] = 0;
    }

    return NO_PROBLEMS;
}