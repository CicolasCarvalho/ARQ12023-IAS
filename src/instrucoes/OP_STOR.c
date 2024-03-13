#include "OP_STOR.h"

void op_stor_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    // funcao de busca de operandos
}

void op_stor_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    if (iteracao == 0) ULA_executar(ula, rAC_read(banco), 0, TRANSFERIR);
    *flags |= STOR_EXECUTADO;
}

void op_stor_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    rMBR_load(banco, ula->saida);
    escrever_resultados_memoria(banco, barramento, memoria, MASK);
}