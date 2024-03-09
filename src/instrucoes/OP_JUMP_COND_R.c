#include "OP_JUMP_COND_R.h"

void op_jump_cond_r_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    buscar_operandos(banco, barramento, memoria);
    rMBR_load(banco, rMBR_read(banco) & RIGHT_MASK);
}

void op_jump_cond_r_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    if (iteracao == 0) ULA_executar(ula, rAC_read(banco), 0, MAIOR_IGUAL);
}

void op_jump_cond_r_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    if (ula->saida) {
        rPC_load(banco, rMAR_read(banco));
        rIBR_reset(banco);
        *flags |= PIPELINE_FLUSH;
    }
}