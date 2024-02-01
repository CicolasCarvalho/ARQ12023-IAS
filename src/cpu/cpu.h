#ifndef CPU_H_
#define CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../barramento/barramento.h"

typedef struct _PipelineOpConfigNode PipelineOpConfigNode;

struct _PipelineOpConfigNode {
    INSTRUCAO op;
    short tempo;
    PipelineOpConfigNode *prox;
};

typedef struct {
    PipelineOpConfigNode *tempo_execucao_lista;
} CPUConfig;

typedef struct {
    CPUConfig config;
    UC uc;
    ULA ula;
    Barramento barramento;
} CPU;

CPU *CPU_criar(void);
void CPU_inserir_tempo_operacao(CPU *cpu, INSTRUCAO op, short tempo);
short CPU_get_tempo_operacao(CPU *cpu, INSTRUCAO op);

PipelineOpConfigNode *PipelineConfig_criar(INSTRUCAO op, short tempo);

#endif