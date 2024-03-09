#include "OP_LSH.h"

void op_lsh_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    // funcao de busca de operandos
}

void op_lsh_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    if (iteracao == 0) ULA_executar(ula, rAC_read(banco), 0, LSH);
}

void op_lsh_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    rAC_load(banco, ula->saida);
}