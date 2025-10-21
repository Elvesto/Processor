#include "array.h"

#include <malloc.h>
#include <assert.h>

int arrayInit(Array* arr, uint64_t capacity) {
    assert(arr);
    assert(capacity > 0);

    arr->data = (int*)calloc(capacity, sizeof(int));
    arr->capacity = capacity;
    arr->size = 0;
    
    assert(arr->data);

    return 0;
}

Array* arrayRealloc(Array* arr) {
    assert(arr);

    return arrayNewCap(arr, arr->capacity * 2);
}

Array* arrayNewCap(Array* arr, uint64_t newCap) {
    assert(arr);
    assert(newCap > arr->capacity);
    
    arr->capacity = newCap;

    int* temp = (int*)realloc(arr->data, arr->capacity * sizeof(int));
    if (!temp) {
        arrayDestroy(arr);
        fprintf(stderr, "PIZDEC\n");
        return NULL;
    }
    arr->data = temp;

    assert(arr->data);

    return arr;
}

int arrayDestroy(Array* arr) {
    assert(arr);

    free(arr->data);
    arr->capacity = 0;
    arr->size = 0;

    return 0;
}

int fillArray(Array* arr, int value) {
    assert(arr);
    assert(arr->data);

    for (uint64_t i = arr->size; i < arr->capacity; i++)
        arr->data[i] = value;

    return 0;
}