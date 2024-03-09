#include "OP_LOAD_MQ_M.h"

void op_load_mq_m_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    buscar_operandos(banco, barramento, memoria);
}

void op_load_mq_m_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    if (iteracao == 0) ULA_executar(ula, rMBR_read(banco), 0, TRANSFERIR);
}

void op_load_mq_m_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    rMQ_load(banco, ula->saida);
}