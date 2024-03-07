#ifndef IAS_H_
#define IAS_H_

#include <stdint.h>
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "../cpu/cpu.h"
#include "../utils.h"

typedef struct {
    bool rodando;
    // bool next_IBR;
    // int tamanho;
    // int tamanho_dados;
} IASConfig;

typedef struct {
    IASConfig config;
    CPU *cpu;
    Barramento *barramento;
    Memoria *memoria;
} IAS;

IAS *IAS_criar(CPU *cpu, Barramento *barramento, Memoria *memoria);
void IAS_free(IAS *ias);
void IAS_iniciar(IAS *ias, PALAVRA PC);
void IAS_tick(IAS *ias);

#endif