#include "stack_t.h"

#include <malloc.h>
#include <stdlib.h>

#include "log.h"

StackError stackInit(Stack_t* stack, long long capacity) {
    if (stack == NULL) {
        return PTR_ERROR;
    }

    if (capacity < 0) {
        return SIZE_ERROR;
    }

    stack->data = (TypeElement*)calloc((size_t)capacity + 2, sizeof(TypeElement));
    if (stack->data == NULL) {
        return PTR_ERROR;
    }
    
    stack->capacity = capacity + 2;
    stack->size = 1;

    //CANAREYKA
    stack->data[0] = LEFT_KANAR;
    stack->data[stack->capacity - 1] = RIGHT_KANAR;

    for (long long i = stack->size; i < stack->capacity - 1; i++) {
        stack->data[i] = POIZON;
    }

    return stackVerify(stack);
}

StackError stackPush(Stack_t* stack, TypeElement value) {
    stackVerify(stack);
    //STACK_DUMP(stack, OK);

    long long index = stack->size;
    if (index == stack->capacity - 1) {
        stackUp(stack);
    }

    if (index > stack->capacity - 1) {
        STACK_DUMP(stack, SIZE_ERROR);
        return SIZE_ERROR;
    }
    stack->data[stack->size++] = value;
    //STACK_DUMP(stack, OK);

    stackVerify(stack);
    
    return OK;
}

TypeElement stackPop(Stack_t* stack, StackError* error) {
    if (stackVerify(stack) != OK && error != NULL) {
        *error = stackVerify(stack);
    }
    //STACK_DUMP(stack, OK);
    
    TypeElement temp = {};
    long long index = stack->size - 1;
    if (index < 1) {
        STACK_DUMP(stack, SIZE_ERROR);
        return 0xeda;
    }
    temp = stack->data[index];
    stack->data[index] = 0xeda;
    stack->size--;

    if (stack->size < stack->capacity / 4) {
        stackDown(stack);
    }

    //STACK_DUMP(stack, OK);

    if (stackVerify(stack) != OK && error != NULL)
        *error = stackVerify(stack);

    return temp;
}

StackError stackDestroy(Stack_t* stack) {
    if (stack == NULL) {
        return PTR_ERROR;
    }
    
    free(stack->data);
    stack->data = NULL;
    stack->capacity = -1;
    stack->size = -1;

    return OK;
}

StackError stackVerify(Stack_t* stack) {
    if (stack == NULL) {
        STACK_DUMP(stack, PTR_ERROR);
        return PTR_ERROR;
    }

    if (stack->data == NULL) {
        STACK_DUMP(stack, PTR_ERROR);
        return PTR_ERROR;
    }

    if (stack->data[0] != LEFT_KANAR || stack->data[stack->capacity - 1] != RIGHT_KANAR) {
        STACK_DUMP(stack, SEG_ERROR);
        return SEG_ERROR;
    }

    if (stack->size < 0 || stack->capacity < 0 || stack->capacity < stack->size) {
        STACK_DUMP(stack, SIZE_ERROR);
        return SIZE_ERROR;
    }

    return OK;
}


void stackDump(Stack_t* stack, const char* file, const char* func, size_t line, StackError error) {
    if (error == OK) {
        logWrite
        (
            INFO, "stack: [%x]\n"
            "in %s:%d \t in %s\n", 
            stack, file, line, func
        );
    } else {
        logWrite
        (
            DEBUG, "stack[%x]\n"
            "in %s:%d \t in %s \t exception: %s\n", 
            stack, file, line, func, errorToString(error)
        );
    }

    logWrite
    (
        INFO, "data[%x] \n"
        "size: %ld \n"
        "capacity: %ld\n", stack->data, stack->size, stack->capacity
    );
    logWrite(INFO, "!!![0]!!! = %d - LEFT CANAR (expected %d)\n", stack->data[0], LEFT_KANAR);
    for (long long i = 1; i < stack->size; i++) {
        logWrite(INFO, "*[%ld] = %d\n", i, stack->data[i]);
    }

    for (long long i = stack->size; i < stack->capacity - 1; i++) {
        logWrite(INFO, "*[%ld] = %d (POIZON)\n", i, stack->data[i]);
    }
    logWrite(INFO, "!!![%ld]!!! = %d - RIGHT CANAR (expected %d)\n\n\n", stack->capacity - 1, stack->data[stack->capacity - 1], RIGHT_KANAR);

}

const char* errorToString(StackError error) {
    switch (error) {
        case OK: return "NO PROBLEMS";
        case SIZE_ERROR: return "SIZE_ERROR";
        case PTR_ERROR: return "PTR_ERROR";
        case SEG_ERROR: return "SEG_ERROR";
        default: return "RAZRAB DAUN V STEKE";
    }
}

StackError stackUp(Stack_t* stack) {
    stackVerify(stack);

    //STACK_DUMP(stack, OK);

    TypeElement* temp = (TypeElement*)realloc(stack->data, stack->capacity * RESIZE * sizeof(TypeElement));
    if (temp == NULL) {
        stackDestroy(stack);
        exit(PTR_ERROR);
    }
    stack->data = temp;
    stack->capacity *= RESIZE;
    stack->data[stack->capacity- 1] = RIGHT_KANAR;

    for (long long i = stack->size; i < stack->capacity - 1; i++) {
        stack->data[i] = POIZON;
    }

    //STACK_DUMP(stack, OK);

    return stackVerify(stack);
}

StackError stackDown(Stack_t* stack) {
    stackVerify(stack);
    TypeElement* temp = (TypeElement*)realloc(stack->data, (stack->capacity / RESIZE) * sizeof(TypeElement));
    if (temp == NULL) {
        stackDestroy(stack);
        exit(PTR_ERROR);
    }
    stack->data = temp;
    stack->capacity /= RESIZE;
    stack->data[stack->capacity - 1] = RIGHT_KANAR;

    for (long long i = stack->size; i < stack->capacity - 1; i++) {
        stack->data[i] = POIZON;
    }

    return stackVerify(stack);
}