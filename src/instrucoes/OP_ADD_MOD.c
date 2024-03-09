#include "OP_ADD_MOD.h"

void op_add_mod_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    buscar_operandos(banco, barramento, memoria);
}

void op_add_mod_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    // if (iteracao == 0) ULA_executar(ula, rMBR_read(banco), rAC_read(banco), SOMAR);
    if (iteracao == 0) ULA_executar(ula, rMBR_read(banco), rAC_read(banco), SOMAR_MOD);
}

void op_add_mod_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    rAC_load(banco, ula->saida);
}