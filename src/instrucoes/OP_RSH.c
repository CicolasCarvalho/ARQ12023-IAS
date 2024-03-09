#include "OP_RSH.h"

void op_rsh_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    // funcao de busca de operandos
}

void op_rsh_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    if (iteracao == 0) ULA_executar(ula, rAC_read(banco), 0, RSH);
}

void op_rsh_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    rAC_load(banco, ula->saida);
}