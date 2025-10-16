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

int arrayRealloc(Array* arr);

int arrayDestroy(Array* arr);

#endif // ARRAY_H_