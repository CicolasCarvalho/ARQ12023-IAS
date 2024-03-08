#include "./pipeline.h"

// insercao em uma lista ligada
void pipeline_inserir_tempo_operacao(Pipeline *pipeline, INSTRUCAO op, short tempo) {
    // PRINT("op: %s tempo: %i", optoa(op), tempo);

    if (op == OP_EXIT) op = 0;

    pipeline->instrucoes[op].tempo = tempo;

    if (op == OP_JUMP_COND_L)
        pipeline->instrucoes[OP_JUMP_COND_R].tempo = tempo;
    else if (op == OP_JUMP_COND_R)
        pipeline->instrucoes[OP_JUMP_COND_L].tempo = tempo;

    if (op == OP_JUMP_L)
        pipeline->instrucoes[OP_JUMP_R].tempo = tempo;
    else if (op == OP_JUMP_R)
        pipeline->instrucoes[OP_JUMP_L].tempo = tempo;
}

InstrucaoConfig pipeline_get_instrucao(Pipeline pipeline, INSTRUCAO op) {
    if (op == OP_EXIT) op = 0;
    return pipeline.instrucoes[op];
}

void pipeline_set_instrucao(
        Pipeline *pipeline, INSTRUCAO op, FUN_BUSCA_OPERANDOS(f_busca_operandos), FUN_EXECUCAO(f_executar), FUN_ESCRITA_RESULTADOS(f_escrita_resultados)) {
    if (op == OP_EXIT) op = 0;

    pipeline->instrucoes[op].f_busca_operandos = f_busca_operandos;
    pipeline->instrucoes[op].f_executar = f_executar;
    pipeline->instrucoes[op].f_escrita_resultados = f_escrita_resultados;
}

void pipeline_buscar_instrucao(
        Pipeline *pipeline, PALAVRA *p1_MBR, BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {

    pipeline->f_buscar_instrucao(banco, barramento, memoria);

    *p1_MBR = banco->rMBR;

    if (pipeline->f_decodificar == NULL) pipeline->f_decodificar = decodificar;
}

void pipeline_decodificar(
        Pipeline *pipeline, PALAVRA p1_MBR, PALAVRA *p2_IR, PALAVRA *p2_MAR, BancoRegistradores *banco) {

    banco->rMBR = p1_MBR;

    pipeline->f_decodificar(banco);
    pipeline->f_decodificar = NULL;

    *p2_IR  = banco->rIR;
    *p2_MAR = banco->rMAR;

    pipeline->f_busca_operandos = pipeline_get_instrucao(*pipeline, banco->rIR).f_busca_operandos;
}

void pipeline_buscar_operandos(
        Pipeline *pipeline, PALAVRA p2_IR, PALAVRA p2_MAR, PALAVRA *p3_IR, BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {

    banco->rMAR = p2_MAR;

    pipeline->f_busca_operandos(banco, barramento, memoria);
    pipeline->f_busca_operandos = NULL;

    *p3_IR = p2_IR;

    pipeline->f_executar = pipeline_get_instrucao(*pipeline, p2_IR).f_executar;

    PRINT("%s: %ld %ld", optoa(p2_IR), banco->rMAR, banco->rMBR);
}

void pipeline_executar(
        Pipeline *pipeline, PALAVRA p3_IR, PALAVRA *p4_MAR, PALAVRA *p4_MBR, BancoRegistradores *banco, ULA *ula) {
    pipeline->f_executar(pipeline->ciclo_execucao++, banco, ula);

    InstrucaoConfig inst = pipeline_get_instrucao(*pipeline, p3_IR);
    if (pipeline->ciclo_execucao >= inst.tempo) {
        // if (pipeline->ciclo_execucao >= 1) {
        pipeline->ciclo_execucao = 0;
        pipeline->f_executar = NULL;

        *p4_MAR = banco->rMAR;
        *p4_MBR = banco->rMBR;

        pipeline->f_escrita_resultados = inst.f_escrita_resultados;
    }
}

void pipeline_escrita_resultados(
        Pipeline *pipeline, PALAVRA p4_MBR, PALAVRA p4_MAR, BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {

    banco->rMBR = p4_MBR;
    banco->rMAR = p4_MAR;

    pipeline->f_escrita_resultados(banco, barramento, memoria);
    pipeline->f_escrita_resultados = NULL;
}
