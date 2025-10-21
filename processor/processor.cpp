#include "processor.h"

#include <string.h>

#include "../stack/stack_t.h"
#include "../array/array.h"
#include "../logs/log.h"
#include "../instruments/tools.h"

ProcessorErrors procInit(Processor* proc, FILE* byteCode) {
    if (!proc) {
        return INIT_ERROR;
    }

    stackInit(&(proc->stack), 14);
    stackInit(&(proc->returnAddress), 14);

    arrayInit(&(proc->instructions), sizeFile(byteCode));

    proc->ip = 0;
    proc->instructions.size = proc->instructions.capacity - 1;

    for (uint64_t i = 0; i < proc->instructions.capacity; i++) {
        proc->instructions.data[i] = 0;
    }

    for (int i = 0; i < COUNT_REGISTERS; i++) {
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

ProcessorErrors procVerify(Processor* proc) {
    if (!proc) {
        return NULL_POINTER;
    }

    if (stackVerify(&proc->stack) || stackVerify(&proc->returnAddress)) {
        PROC_DUMP(proc);
        return STACK_ERROR;
    }

    if (proc->ip < 0) {
        PROC_DUMP(proc);
        return POINTER_ERROR;
    }

    return NO_PROBLEMS;
}

int procDump(Processor* proc, const char* f, const char* func, int line) {
    logWrite
    (
        DEBUG, "Processor[%x]\n"
        "in %s:%d \t in %s\n",
        proc, f, line, func
    );
    logWrite
    (
        INFO, "Processor[%x]\n"
        "ip = %d\n"
        "instructions(array): size = %d, capcity = %d",
        proc, proc->ip, proc->instructions.size, proc->instructions.capacity
    );
    for (int i = 0; i < COUNT_REGISTERS; i++) {
        logWrite(DEBUG, "registers[%d] = %d", i, proc->regs[i]);
    }
    logWrite(DEBUG, "-----------------PROCESSORS STACK-----------------");
    STACK_DUMP(&proc->stack, OK);
    logWrite(DEBUG, "-------------PROCESSORS RETURN ADDRESS------------");
    STACK_DUMP(&proc->returnAddress, OK);
    logWrite(DEBUG, "---------------------END--------------------------");

    return 0;
}