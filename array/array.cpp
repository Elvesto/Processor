#include "array.h"

#include <malloc.h>
#include <assert.h>

int arrayRealloc(Array* arr) {
    int* temp = (int*)realloc(arr->data, arr->capacity * 2 * sizeof(int));
    if (!temp) {
        free(arr->data);
        return 1;
    }
    arr->data = temp;
    assert(arr->data);
    return 0;
}