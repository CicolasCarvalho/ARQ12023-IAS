#include "OP_JUMP_COND_L.h"

void op_jump_cond_l_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    buscar_operandos(banco, barramento, memoria);
}

void op_jump_cond_l_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    if (iteracao == 0) ULA_executar(ula, rAC_read(banco), 0, MAIOR_IGUAL);
}

void op_jump_cond_l_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    if (ula->saida) {
        rPC_load(banco, rMAR_read(banco));
        rIBR_reset(banco);
        rPC_increment(banco);
        *flags |= PIPELINE_FLUSH;
    }
}