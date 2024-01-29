#ifndef IAS_H_
#define IAS_H_

#include <stdint.h>
#include "../memoria/memoria.h"
#include "../cpu/cpu.h"

typedef struct {
    // int tamanho;
    // int tamanho_dados;
} IASConfig;

typedef struct {
    IASConfig config;
    CPU *cpu;
    Memoria *memoria;
} IAS;

IAS *IAS_criar(void);
void IAS_tick(void);

#endif