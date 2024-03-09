#include "OP_EXIT.h"

void op_exit_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    // nada
}

void op_exit_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    *flags |= STOP;
}

void op_exit_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    // nada
}