#include "OP_JUMP_R.h"

void op_jump_r_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    buscar_operandos(banco, barramento, memoria);
}

void op_jump_r_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags) {
    // funcao de execucao
}

void op_jump_r_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags) {
    rPC_load(banco, rMAR_read(banco));
    rIBR_reset(banco);
    *flags |= PIPELINE_FLUSH;
}