#include "./ias.h"

IAS *IAS_criar(CPU *cpu, Barramento *barramento, Memoria *memoria) {
    IAS *ias = malloc(sizeof(IAS));

    ias->config = (IASConfig){
        .rodando = false,
    };
    ias->cpu = cpu;
    ias->barramento = barramento;
    ias->memoria = memoria;

    return ias;
}

void IAS_free(IAS *ias) {
    CPU_free(ias->cpu);
    barramento_free(ias->barramento);
    memoria_free(ias->memoria);
    free(ias);
}

void IAS_iniciar(IAS *ias, PALAVRA PC) {
    ias->config.rodando = true;
    ias->cpu->banco_regs.rPC = PC;
}

void IAS_tick(IAS *ias) {
    CPU_tick(ias->cpu, ias->barramento, ias->memoria);

    ias->config.rodando = (char)!(ias->cpu->uc->pipeline->flags & STOP) ;
}