#include "calc.h"

#include <string.h>
#include <math.h>
#include <assert.h>

#include "tools.h"
#include "stack/stack_t.h"
#include "array/array.h"

StackError executor(Processor* proc) {
    if (proc == NULL)
        return PTR_ERROR;

    Stack* stack = &(proc->stack);
    Array* instructions = &(proc->instructions);

    StackError err = OK;

    for (proc->ip = 0; proc->ip < instructions->capacity; proc->ip++) {
        switch (instructions->data[proc->ip]) {
            case PUSH:
            {
                TypeElement temp = (instructions->data)[++(proc->ip)];
                err = stackPush(stack, temp);
                if (err) {
                    return err;
                }

                break;
            }
            case ADD: 
            {
                int temp1 = 0, temp2 = 0;
                
                temp1 = stackPop(stack, &err);
                if (err) {
                    return err;
                }

                temp2 = stackPop(stack, &err);
                if (err) {
                    return err;
                }

                if (temp1 != POIZON && temp2 != POIZON) {
                    err = stackPush(stack, temp1 + temp2);
                    if (err) {
                        return err;
                    }
                } else
                    printf("Not enough arguments on the stack\n");

                break;
            }
            case SUB:
            {
                int temp1 = 0, temp2 = 0;

                temp2 = stackPop(stack, &err);
                if (err) {
                    return err;
                }

                temp1 = stackPop(stack, &err);
                if (err) {
                    return err;
                }

                if (temp1 != POIZON && temp2 != POIZON) {
                    err = stackPush(stack, temp1 - temp2);
                    if (err) {
                        return err;
                    }
                } else
                    printf("Not enough arguments on the stack\n");

                break;
            }
            case MUL:
            {
                int temp1 = 0, temp2 = 0;
                temp1 = stackPop(stack, &err);
                // printf("%d\n", temp1);
                if (err) {
                    return err;
                }

                temp2 = stackPop(stack, &err);
                if (err) {
                    return err;
                }

                if (temp1 != POIZON && temp2 != POIZON) {
                    err = stackPush(stack, temp1 * temp2);
                    if (err) {
                        return err;
                    }
                    
                } else
                    printf("Not enough arguments on the stack\n");

                break;
            }
            case DIV:
            {
                double temp1 = 0, temp2 = 0;

                temp2 = stackPop(stack, &err);
                if (err) {
                    return err;
                }

                temp1 = stackPop(stack, &err);
                if (err) {
                    return err;
                }

                if (!equal(temp1, (double)POIZON) && !equal(temp2,(double)POIZON)) {
                    err = stackPush(stack, (TypeElement)(temp1 / temp2));
                    if (err) {
                        return err;
                    }
                } else
                    printf("Not enough arguments on the stack\n");

                break;
            }
            case SQRT:
            {
                double temp = 0;

                temp = stackPop(stack, &err);
                if (err) {
                    return err;
                }

                if (!equal(temp, (double)POIZON)) {
                    temp = sqrt(temp);
                    
                    err = stackPush(stack, (TypeElement)(temp));
                    if (err) {
                        return err;
                    }
                } else
                    printf("Not enough arguments on the stack\n");

                break;
            }
            case OUT:
            {
                TypeElement temp = stackPop(stack, &err);
                if (err) {
                    return err;
                }

                // if (temp != POIZON) {
                printf("%lf\n", (double)temp);
                // } else {
                //     printf("No element\n");
                // }

                break;
            }
            case HLT:
            {
                return OK;
            }
            default:
            {
                printf("razrab daun tak kak - %d\n", instructions->data[proc->ip]);
                return OK;
                break;
            }
        }
    }
    return OK;
}