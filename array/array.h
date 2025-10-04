#ifndef ARRAY_H_
#define ARRAY_H_

typedef struct {
    int* data;
    unsigned int size;
    unsigned int capacity;
} Array;

//TODO 
int arrayCtor(Array* arr);

int arrayDtor(Array* arr);

#endif // ARRAY_H_