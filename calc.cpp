#include "calc.h"

#include <string.h>

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
        printf("%d\n", stackPop(stack) / 1000);
    } else if (strcmp(command, "HLT") == 0) {
        return SEG_ERROR;
    }
    return OK;
}