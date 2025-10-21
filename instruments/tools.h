#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdint.h>
#include <stdio.h>

typedef struct {
    char* name;
    FILE* file;
} FileParam;

const double EPS = 1e-5;

int equal(double num1, double num2);

uint64_t sizeFile(FILE* file);

char* bufCreate(FileParam* file);

size_t getCountString(char* buf);

#endif // TOOLS_H_