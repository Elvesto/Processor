#include "stack_t.h"

#include <malloc.h>
#include <stdlib.h>

#include "../logs/log.h"

StackError stackInit(Stack* stack, long long capacity) {
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

StackError stackPush(Stack* stack, TypeElement value) {
    if (stackVerify(stack)) {
        return stackVerify(stack);
    }
    //STACK_DUMP(stack, OK);

    long long index = stack->size;
    if (index == stack->capacity - 1) {
        stackRealloc(stack, RESIZE);
    }

    stack->data[stack->size++] = value;
    //STACK_DUMP(stack, OK);

    if (stackVerify(stack)) {
        return stackVerify(stack);
    }
    
    return OK;
}

TypeElement stackPop(Stack* stack, StackError* error) {
    STACK_DUMP(stack, OK);
    if (stackVerify(stack) && error) {
        *error = stackVerify(stack);
        return 0;
    }
    
    TypeElement temp = {};
    long long index = stack->size - 1;
    
    if (index < 1) {
        STACK_DUMP(stack, SIZE_ERROR);
        if (error)
            *error = GET_POIZON;
        return 0;
    }

    temp = (stack->data)[index];

    if (temp != POIZON) {
        stack->data[index] = POIZON;
        stack->size--;
    } else {
        STACK_DUMP(stack, SEG_ERROR);
        if (error)
            *error = GET_POIZON;
        return 0;
    }

    if (stack->size < stack->capacity / 4) {
        if (stackRealloc(stack, 1 / RESIZE) != 0) {
            if (error)
                *error = PTR_ERROR;
            return 0;
        }
    }

    if (stackVerify(stack) && error) {
        *error = stackVerify(stack);
        return 0;
    }
    return temp;
}

StackError stackDestroy(Stack* stack) {
    if (stack == NULL) {
        return PTR_ERROR;
    }
    
    free(stack->data);
    stack->data = NULL;
    stack->capacity = -1;
    stack->size = -1;

    return OK;
}

StackError stackVerify(Stack* stack) {
    if (stack == NULL) {
        STACK_DUMP(stack, PTR_ERROR);
        return PTR_ERROR;
    }

    if (stack->data == NULL) {
        STACK_DUMP(stack, PTR_ERROR);
        return PTR_ERROR;
    }

    if (stack->size < 0 || stack->capacity < 0 || stack->capacity < stack->size) {
        STACK_DUMP(stack, SIZE_ERROR);
        return SIZE_ERROR;
    }

    if (stack->data[0] != LEFT_KANAR || stack->data[stack->capacity - 1] != RIGHT_KANAR) {
        STACK_DUMP(stack, SEG_ERROR);
        return SEG_ERROR;
    }

    return OK;
}

//FIXME Сделать всё по красоте, печатать первые n символов и последние n символов
void stackDump(Stack* stack, const char* file, const char* func, size_t line, StackError error) {
    
    logWrite
    (
        DEBUG, "stack[%x]\n"
        "in %s:%d \t in %s \t exception: %s\n", 
        stack, file, line, func, errorToString(error)
    );

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
        logWrite(INFO, "  *[%ld]   = %d (POIZON)\n", i, stack->data[i]);
    }
    logWrite(INFO, "!!![%ld]!!! = %d - RIGHT CANAR (expected %d)\n\n\n", stack->capacity - 1, stack->data[stack->capacity - 1], RIGHT_KANAR);

}

const char* errorToString(StackError error) {
    switch (error) {
        case OK: return "NO PROBLEMS";
        case SIZE_ERROR: return "SIZE_ERROR";
        case PTR_ERROR: return "PTR_ERROR";
        case SEG_ERROR: return "SEG_ERROR";
        case GET_POIZON: return "TRY GETTING POIZON";
        default: return "RAZRAB DAUN V STEKE";
    }
}

//FIXME Одна функция stackRealloc
StackError stackRealloc(Stack* stack, float factor) {
    if (stackVerify(stack)) {
        return stackVerify(stack);
    }

    //STACK_DUMP(stack, OK);

    TypeElement* temp = (TypeElement*)realloc(stack->data, (unsigned long long)((double)stack->capacity * factor * sizeof(TypeElement)));
    if (temp == NULL) {
        return PTR_ERROR;
    }
    stack->data = temp;
    stack->capacity = (long long)((double)stack->capacity * factor);
    stack->data[stack->capacity- 1] = RIGHT_KANAR;

    for (long long i = stack->size; i < stack->capacity - 1; i++) {
        stack->data[i] = POIZON;
    }

    // STACK_DUMP(stack, OK);
    // printf("%d\n", stackVerify(stack));

    return stackVerify(stack);
}



long long getSize(Stack* stack) {
    if (stackVerify(stack)) {
        return stackVerify(stack);
    }

    return stack->size - 1;
}

long long getCapacity(Stack* stack) {
    if (stackVerify(stack)) {
        return stackVerify(stack);
    }

    return stack->capacity - 2;
}

TypeElement peak(Stack* stack) {
    stackVerify(stack);

    return stack->data[stack->size - 1];
}