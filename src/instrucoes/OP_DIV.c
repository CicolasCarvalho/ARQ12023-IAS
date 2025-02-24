#include "OP_DIV.h"

void op_div_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    buscar_operandos(banco, barramento, memoria);
}

void op_div_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    if (iteracao == 0) ULA_executar(ula, rAC_read(banco), rMBR_read(banco), DIVIDIR);
}

void op_div_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    rMQ_load(banco, ula->saida);
    rAC_load(banco, ula->overflow);
}