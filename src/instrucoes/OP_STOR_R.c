#include "OP_STOR_R.h"

void op_stor_r_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    // funcao de busca de operandos
}

void op_stor_r_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    if (iteracao == 0) ULA_executar(ula, rAC_read(banco), 0, TRANSFERIR);
}

void op_stor_r_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    // TODO: ESCRITA PARCIAL NA MEMORIA
    rMBR_load(banco, ula->saida & ARGUMENTO_MASK);
    escrever_resultados_memoria(banco, barramento, memoria, RIGHT_MASK);
}