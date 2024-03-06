#include "./pipeline.h"

// insercao em uma lista ligada
void pipeline_inserir_tempo_operacao(Pipeline *pipeline, INSTRUCAO op, short tempo) {
    // PRINT("op: %s tempo: %i", optoa(op), tempo);

    if (op == OP_EXIT) op = !op;

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

short pipeline_get_tempo_operacao(Pipeline *pipeline, INSTRUCAO op) {
    if (op == OP_EXIT) op = !op;
    return pipeline->instrucoes[op].tempo;
}

void pipeline_set_instrucao(Pipeline *pipeline, INSTRUCAO op,
                            FUN_BUSCA_OPERANDOS(f_busca_operandos),
                            FUN_EXECUCAO(f_executar),
                            FUN_ESCRITA_RESULTADOS(f_escrita_resultados)) {
    pipeline->instrucoes[op].f_busca_operandos = f_busca_operandos;
    pipeline->instrucoes[op].f_executar = f_executar;
    pipeline->instrucoes[op].f_escrita_resultados = f_escrita_resultados;
}