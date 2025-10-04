#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>

#define STACK_DUMP(stack, error) stackDump(stack, __FILE__, __FUNCTION__, __LINE__, error);

typedef int TypeElement;

const TypeElement LEFT_KANAR = 0b00101011101000101011100100011100;
const TypeElement RIGHT_KANAR = 0b01010100010111010100011011100011;

const TypeElement POIZON = 0xEDA;

const float RESIZE = 2.0;

typedef struct {
    TypeElement* data;
    long long size;
    long long capacity;
} Stack;

enum StackError{
    OK = 0,
    SIZE_ERROR = 1,
    PTR_ERROR = 2,
    SEG_ERROR = 3,
    GET_POIZON = 4
};

StackError stackInit(Stack* stack, long long capacity);

StackError stackPush(Stack* stack, TypeElement value);

TypeElement stackPop(Stack* stack, StackError* error = NULL);

StackError stackDestroy(Stack* stack);

StackError stackVerify(Stack* stack);

void stackDump(Stack* stack, const char* file, const char* func, size_t line, StackError error);

const char* errorToString(StackError error);

StackError stackRealloc(Stack* stack, float factor);

long long getSize(Stack* stack);

long long getCapacity(Stack* stack);

TypeElement peak(Stack* stack);


#endif // STACK_H_