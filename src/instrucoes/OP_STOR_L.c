#include "OP_STOR_L.h"

void op_stor_l_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    // funcao de busca de operandos
}

void op_stor_l_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    if (iteracao == 0) ULA_executar(ula, rAC_read(banco), 0, TRANSFERIR);
}

void op_stor_l_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    rMBR_load(banco, ula->saida);
    escrever_resultados_memoria(banco, barramento, memoria, LEFT_MASK);
    *flags |= STOR_PARCIAL_FINALIZADO;
}