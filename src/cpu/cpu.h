#ifndef CPU_H_
#define CPU_H_

#include "../uc/uc.h"
#include "../ula/ula.h"

typedef struct {
    INSTRUCAO op;
    short tempo;
} PipelineOpConfig;

typedef struct {
    PipelineOpConfig tempo_execucao[NUM_INSTRUCOES];
} CPUConfig;

typedef struct {
    CPUConfig config;
    UC uc;
    ULA ula;
} CPU;

CPU *CPU_criar(void);
void CPU_inserir_configuracao(CPU *cpu, INSTRUCAO op, short tempo);

#endif