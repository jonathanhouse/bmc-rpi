#include "base.h"

void write32(void *reg, unsigned int x){
    volatile unsigned int* reg32 = (unsigned int*)reg;
    *reg32 = x;
}

unsigned int read32(void *reg){
    volatile unsigned int* reg32 = (unsigned int*)reg;
    return *reg32;
}