#include "disAsm.h"

#include "../array/array.h"
#include "../processor/processor.h"

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
            case PUSHR:
            {
                fprintf(out->file, "PUSH %s\n", regToStr((Registers)arr->data[++i]));
                break;
            }
            case POPR: {
                fprintf(out->file, "POPR %s\n", regToStr((Registers)arr->data[++i]));
                break;
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

const char* regToStr(Registers reg) {
    switch (reg) {
        case RESERVED: return "RESERVED";
        case RAX: return "RAX";
        case RBX: return "RBX";
        case RCX: return "RCX";
        case RDX: return "RDX";
        case REX: return "REX";
        case RFX: return "RFX";
        case RGX: return "RGX";
        default: return "razrab daun";
    }
}