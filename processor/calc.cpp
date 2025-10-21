#include "calc.h"

#include <string.h>
#include <math.h>
#include <assert.h>

#include "../instruments/tools.h"
#include "../stack/stack_t.h"
#include "../array/array.h"

ProcessorErrors executor(Processor* proc) {
    if (proc == NULL)
        return NULL_POINTER;

    //Array* instructions = &(proc->instructions);
    // static Array labels = {};
    // arrayInit(&labels, 32);

    StackError err = OK;
    // printf("capcity instruct - %d", instructions->capacity);

    for (proc->ip = 0; proc->ip < (int64_t)proc->instructions.size; proc->ip++) {
        if (proc->instructions.data[proc->ip] <= RET)
        {
            if (execute[proc->instructions.data[proc->ip]].func(proc) == EXIT) break;
        } else {
            if (proc->instructions.data[proc->ip] == 20) continue;
            fprintf(stderr, "CHTO-TO NE TAK --------- %d\n", proc->instructions.data[proc->ip]);
            break;
        }
    }
    return (ProcessorErrors)err;
}

ProcessorErrors hltFunc(Processor* proc) {
    return EXIT;
}

ProcessorErrors pushFunc(Processor* proc) {
    StackError err = {};
    TypeElement temp = (proc->instructions.data)[++(proc->ip)];
    err = stackPush(&proc->stack, temp);
    if (err) {
        return STACK_ERROR;
    }

    return NO_PROBLEMS;
}

ProcessorErrors opFunc(Processor* proc) {
    StackError err = {};
    Stack* stack = &proc->stack;
    switch (proc->instructions.data[proc->ip]) {
        case ADD:
        {
            OPERATION(+);
            break;
        }
        case SUB:
        {
            OPERATION(-);
            break;
        }
        case MUL:
        {
            OPERATION(*);
            break;
        }
        case DIV:
        {
            OPERATION(/);
            break;
        }
        default:
        {
            fprintf(stderr, "PIZDEC\n");
        }
    }

    return NO_PROBLEMS;
}

ProcessorErrors sqrtFunc(Processor* proc) {
    double temp = 0;
    StackError err = {};

    Stack* stack = &proc->stack;

    temp = stackPop(stack, &err);
    if (err) {
        return STACK_ERROR;
    }

    temp = sqrt(temp);
    
    err = stackPush(stack, (TypeElement)(temp));
    if (err) {
        return STACK_ERROR;
    }

    return NO_PROBLEMS;
}

ProcessorErrors outFunc(Processor* proc) {
    StackError err = {};
    Stack* stack = &proc->stack;
    TypeElement temp = stackPop(stack, &err);
    if (err) {
        return STACK_ERROR;
    }

    printf("%lf\n", (double)temp);

    return NO_PROBLEMS;
}

ProcessorErrors pushRFunc(Processor* proc) {
    StackError err = {};
    TypeElement temp = proc->regs[proc->instructions.data[++proc->ip]];
    Stack* stack = &proc->stack;
    err = stackPush(stack, temp);
    if (err) {
        return STACK_ERROR;
    }

    return NO_PROBLEMS;
}

ProcessorErrors popRFunc(Processor* proc) {
    StackError err = {};
    Stack* stack = &proc->stack;
    TypeElement temp = stackPop(stack, &err);
    if (err) {
        return STACK_ERROR;
    }
    proc->regs[proc->instructions.data[++proc->ip]] = temp;

    return NO_PROBLEMS;
}

ProcessorErrors inFunc(Processor* proc) {
    int temp = 0;
    Stack* stack = &proc->stack;
    scanf("%d", &temp);
    StackError err = stackPush(stack, temp);
    if (err) {
        printf("ERROR\n");
        return STACK_ERROR;
    }

    return NO_PROBLEMS;
}

ProcessorErrors jmpFunc(Processor* proc) {
    StackError err = {};
    Stack* stack = &proc->stack;
    switch (proc->instructions.data[proc->ip]) {
        case JMP:
        {
            int temp = proc->instructions.data[++(proc->ip)];
            proc->ip = temp;
            break;
        }
        case JB:
        {
            JUMP_IF(<);
            break;
        }
        case JBE:
        {
            JUMP_IF(<=);
            break;
        }
        case JA:
        {
            JUMP_IF(>);
            break;
        }
        case JAE:
        {
            JUMP_IF(>=);
            break;
        }
        case JE:
        {
            JUMP_IF(==);
            break;
        }
        case JNE:
        {
            JUMP_IF(!=);
            break;
        }
        case CALL:
        {
            stackPush(&(proc->returnAddress), (int)proc->ip + 1);
            int temp = proc->instructions.data[++(proc->ip)];
            proc->ip = temp + 1;
            break;
        }
        case RET:
        {
            proc->ip = stackPop(&(proc->returnAddress), &err);
            break;
        }
        default:
        {
            fprintf(stderr, "PIZDEC\n");
            break;
        }
    }

    return NO_PROBLEMS;
}

ProcessorErrors nothing(Processor* proc) {
    return NO_PROBLEMS;
}