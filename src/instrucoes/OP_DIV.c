#include "OP_DIV.h"

void op_div_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    buscar_operandos(banco, barramento, memoria);
}

void op_div_executar(int iteracao, BancoRegistradores *banco, ULA *ula) {
    if (iteracao == 0) ULA_executar(ula, rMBR_read(banco), 0, DIVIDIR);
}

void op_div_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula) {
    rMQ_load(banco, ula->saida);
    rAC_load(banco, ula->overflow);
}