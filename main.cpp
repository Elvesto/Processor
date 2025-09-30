#include <stdio.h>

#include <assert.h>

#include "stack_t.h"
#include "log.h"
#include "calc.h"

int main() {
    openLog("test.txt");
    
    Stack_t stk = {};
    stackInit(&stk, 30);

    while (!getCommand(&stk));
    
    stackDestroy(&stk);
    
    closeLog();
}