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

    Stack* stack = &(proc->stack);
    Array* instructions = &(proc->instructions);
    // static Array labels = {};
    // arrayInit(&labels, 32);

    StackError err = OK;
    // printf("capcity instruct - %d", instructions->capacity);

    for (proc->ip = 0; proc->ip < (int64_t)instructions->capacity; proc->ip++) {
        // printf("command - %d\n", instructions->data[proc->ip]);
        switch (instructions->data[proc->ip]) {
            case PUSH:
            {
                TypeElement temp = (instructions->data)[++(proc->ip)];
                err = stackPush(stack, temp);
                if (err) {
                    return STACK_ERROR;
                }

                break;
            }
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
            case SQRT:
            {
                double temp = 0;

                temp = stackPop(stack, &err);
                if (err) {
                    return STACK_ERROR;
                }

                temp = sqrt(temp);
                
                err = stackPush(stack, (TypeElement)(temp));
                if (err) {
                    return STACK_ERROR;
                }

                break;
            }
            case OUT:
            {
                TypeElement temp = stackPop(stack, &err);
                if (err) {
                    return STACK_ERROR;
                }

                printf("%lf\n", (double)temp);

                break;
            }
            case HLT:
            {
                return NO_PROBLEMS;
            }
            case PUSHR:
            {
                TypeElement temp = proc->regs[instructions->data[++proc->ip]];
                err = stackPush(stack, temp);
                if (err) {
                    return STACK_ERROR;
                }
                break;
            }
            case POPR:
            {
                TypeElement temp = stackPop(stack, &err);
                if (err) {
                    return STACK_ERROR;
                }
                proc->regs[instructions->data[++proc->ip]] = temp;
                break;
            }
            case JMP:
            {
                int temp = instructions->data[++(proc->ip)];
                proc->ip = temp + 1;
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
                int temp = instructions->data[++(proc->ip)];
                proc->ip = temp;
                break;
            }
            case RET:
            {
                proc->ip = stackPop(&(proc->returnAddress), &err);
                break;
            }
            case IN:
            {
                int temp = 0;
                scanf("%d", &temp);
                err = stackPush(stack, temp);
                if (err) {
                    printf("ERROR\n");
                    return STACK_ERROR;
                }
                break;
            }
            case LABEL:
            {
                proc->ip++;
                break;
            }
            default:
            {
                printf("razrab daun tak kak - %d\n", instructions->data[proc->ip]);
                return STRANGE;
                printf("pizdec\n");
            }
        }
    }
    return (ProcessorErrors)err;
}