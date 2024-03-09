#include "OP_EXIT.h"

void op_exit_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    // nada
}

void op_exit_executar(int iteracao, BancoRegistradores *banco, ULA *ula) {
    exit(0);
}

void op_exit_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula) {
    // nada
}