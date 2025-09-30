#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>

#define STACK_DUMP(stack, error) stackDump(stack, __FILE__, __FUNCTION__, __LINE__, error);

typedef int TypeElement;

const TypeElement LEFT_KANAR = 0b00101011101000101011100100011100;
const TypeElement RIGHT_KANAR = 0b01010100010111010100011011100011;

const TypeElement POIZON = 0xEDA;

const int RESIZE = 2;

typedef struct {
    TypeElement* data;
    long long size;
    long long capacity;
} Stack_t;

enum StackError{
    OK = 0,
    SIZE_ERROR = 1,
    PTR_ERROR = 2,
    SEG_ERROR = 3
};

StackError stackInit(Stack_t* stack, long long capacity);

StackError stackPush(Stack_t* stack, TypeElement value);

TypeElement stackPop(Stack_t* stack, StackError* error = NULL);

StackError stackDestroy(Stack_t* stack);

StackError stackVerify(Stack_t* stack);

void stackDump(Stack_t* stack, const char* file, const char* func, size_t line, StackError error);

const char* errorToString(StackError error);

StackError stackUp(Stack_t* stack);

StackError stackDown(Stack_t* stack);


#endif // STACK_H_