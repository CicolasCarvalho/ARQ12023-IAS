#ifndef CPU_H_
#define CPU_H_

#include "../uc/uc.h"
#include "../ula/ula.h"

typedef struct {
    UC uc;
    ULA ula;
} CPU;

CPU *CPU_criar(void);
void CPU_tick(void);

#endif