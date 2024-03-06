#ifndef CPU_H_
#define CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../barramento/barramento.h"
#include "../registradores/registradores.h"

typedef struct {
    BancoRegistradores banco_regs;
    UC *uc;
    ULA *ula;
} CPU;

CPU *CPU_criar(void);
void CPU_tick(CPU *cpu, Barramento *barramento, Memoria *memoria);

#endif