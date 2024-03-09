#include "OP_SUB_MOD.h"

void op_sub_mod_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    buscar_operandos(banco, barramento, memoria);
}

void op_sub_mod_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    if (iteracao == 0) ULA_executar(ula, rAC_read(banco), rMBR_read(banco), SUBTRAIR_MOD);
}

void op_sub_mod_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    rAC_load(banco, ula->saida);
}