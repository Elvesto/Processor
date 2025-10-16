#include "array.h"

#include <malloc.h>
#include <assert.h>

int arrayInit(Array* arr, uint64_t capacity) {
    assert(arr);
    assert(capacity > 0);

    arr->data = (int*)calloc(capacity, sizeof(int));
    arr->capacity = capacity;
    arr->size = 0;
    

    return 0;
}

int arrayRealloc(Array* arr) {
    assert(arr);
    
    int* temp = (int*)realloc(arr->data, arr->capacity * 2 * sizeof(int));
    if (!temp) {
        free(arr->data);
        return 1;
    }
    arr->data = temp;
    assert(arr->data);

    return 0;
}

int arrayDestroy(Array* arr) {
    assert(arr);

    free(arr->data);
    arr->capacity = 0;
    arr->size = 0;

    return 0;
}