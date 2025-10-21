#ifndef ARRAY_H_
#define ARRAY_H_

#include <stdint.h>

typedef struct {
    int* data;
    uint64_t size;
    uint64_t capacity;
} Array;

//TODO 
int arrayInit(Array* arr, uint64_t capacity);

Array* arrayNewCap(Array* arr, uint64_t newSize);

Array* arrayRealloc(Array* arr);

int arrayDestroy(Array* arr);

int fillArray(Array* arr, int value);

#endif // ARRAY_H_