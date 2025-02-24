#include "./cpu.h"

CPU *CPU_criar(void) {
    CPU *cpu = malloc(sizeof(CPU));

    cpu->banco_regs = (BancoRegistradores){
        .rAC  = 0,
        .rMQ  = 0,
        .rMBR = 0,
        .rPC  = 0,
        .rMAR = 0,
        .rIBR = 0,
        .rIR  = 0,
    };
    cpu->uc = UC_criar();
    cpu->ula = ULA_criar();

    return cpu;
}

void CPU_free(CPU *cpu) {
    UC_free(cpu->uc);
    ULA_free(cpu->ula);
    free(cpu);
}

void CPU_tick(CPU *cpu, Barramento *barramento, Memoria *memoria) {
    UC_tick(cpu->uc, cpu->ula, &cpu->banco_regs, barramento, memoria);
}