#include "tools.h"

#include <math.h>

int equal(double num1, double num2) {
    return fabs(num1 - num2) < EPS;
}