#include "OP_MUL.h"

void op_mul_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    buscar_operandos(banco, barramento, memoria);
}

void op_mul_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    if (iteracao == 0) ULA_executar(ula, rMBR_read(banco), rMQ_read(banco), MULTIPLICAR);
}

void op_mul_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    rMQ_load(banco, ula->saida);
    rAC_load(banco, ula->overflow);
}