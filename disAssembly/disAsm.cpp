#include "disAsm.h"

#include "../array/array.h"

int disasm(File* out, Array* arr) {
    for (int i = 0; ; i++) {
        switch (arr->data[i]) {
            case PUSH: 
            {
                fprintf(out->file, "PUSH %d\n", arr->data[++i]);
                break;
            }
            case ADD:
            {
                fprintf(out->file, "ADD\n");
                break;
            }
            case SUB:
            {
                fprintf(out->file, "SUB\n");
                break;
            }
            case MUL:
            {
                fprintf(out->file, "MUL\n");
                break;
            }
            case DIV:
            {
                fprintf(out->file, "DIV\n");
                break;
            }
            case SQRT:
            {
                fprintf(out->file, "SQRT\n");
                break;
            }
            case OUT:
            {
                fprintf(out->file, "OUT\n");
                break;
            }
            case HLT:
            {
                fprintf(out->file, "HLT\n");
                return 1;
            }
            default:
            {
                printf("DATA: %d\t%d\n", arr->data[i], i);
                printf("razrab daun\n");
            }
        }
    }
    return 0;
}