#include "calc.h"

#include <string.h>
#include <math.h>

#include "stack_t.h"

StackError getCommand(Stack_t* stack) {
    char command[10] = {};
    scanf("%s", command);
    if (strcmp(command, "PUSH") == 0) {
        int temp = 0;
        scanf("%d", &temp);
        stackPush(stack, temp*1000);
    } else if (strcmp(command, "ADD") == 0) {
        int temp1 = 0, temp2 = 0;
        temp1 = stackPop(stack);
        temp2 = stackPop(stack);
        stackPush(stack, temp1 + temp2);
    } else if (strcmp(command, "SUB") == 0) {
        int temp1 = 0, temp2 = 0;
        temp1 = stackPop(stack);
        temp2 = stackPop(stack);
        stackPush(stack, temp1 - temp2);
    } else if (strcmp(command, "OUT") == 0) {
        int temp = stackPop(stack);
        if (temp != POIZON) {
            printf("%lf\n", (double)temp / 1000);
        } else {
            printf("No element\n");
        }
    } else if (strcmp(command, "HLT") == 0) {
        printf("Exit...\n");
        return SEG_ERROR;
    } else if (strcmp(command, "DMP") == 0) {
        STACK_DUMP(stack, OK);
        printf("stack dumped\n");
    } else if (strcmp(command, "MUL") == 0) {
        int temp1 = 0, temp2 = 0;
        temp1 = stackPop(stack);
        temp2 = stackPop(stack);
        stackPush(stack, temp1 * temp2 / 1000);
    } else if (strcmp(command, "DIV") == 0) {
        double temp1 = 0, temp2 = 0;
        temp1 = stackPop(stack);
        temp2 = stackPop(stack);
        stackPush(stack, (TypeElement)(temp1 / temp2) * 1000);
    } else if (strcmp(command, "SQVRT") == 0) {
        double temp = 0;
        temp = stackPop(stack) / 1000;
        temp = sqrt(temp);
        stackPush(stack, (TypeElement)(temp * 1000));
    }
    return OK;
}