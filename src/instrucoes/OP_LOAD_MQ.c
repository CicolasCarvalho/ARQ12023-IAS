#include "OP_LOAD_MQ.h"

void op_load_mq_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    // nada
}

void op_load_mq_executar(int iteracao, BancoRegistradores *banco, ULA *ula) {
    // nada
}

void op_load_mq_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula) {
    rAC_load(banco, rMQ_read(banco));
}