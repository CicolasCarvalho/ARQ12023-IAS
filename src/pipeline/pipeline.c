#include "./pipeline.h"

Pipeline *pipeline_criar(void) {
    Pipeline *pipeline = malloc(sizeof(Pipeline));

    pipeline->ciclo_execucao = 0;
    pipeline->flags = 0;

    for (int i = 0; i < FILA_DEPENDENCIA_SIZE; ++i)
        pipeline->fila_dependencia[i].op = 0;

    pipeline->f_buscar_instrucao = NULL;
    pipeline->f_decodificar = NULL;
    pipeline->f_busca_operandos = NULL;
    pipeline->f_executar = NULL;
    pipeline->f_escrita_resultados = NULL;

    return pipeline;
}

void pipeline_free(Pipeline *pipeline) {
    free(pipeline);
}

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

    if (op == OP_STOR_L)
        pipeline->instrucoes[OP_STOR_R].tempo = tempo;
}

InstrucaoConfig pipeline_get_instrucao(Pipeline *pipeline, INSTRUCAO op) {
    if (op == OP_EXIT) op = 0;
    return pipeline->instrucoes[op];
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

    // TODO: COLOCAR MASCARA NA BUSCA INSTRUCAO
    if (pipeline->flags & CARREGAR_DIREITA) {
        rMBR_load(banco, rMBR_read(banco) & RIGHT_MASK);
        pipeline->flags &= ~CARREGAR_DIREITA;
    }

    *p1_MBR = banco->rMBR;

    pipeline->f_decodificar = decodificar;
}

void pipeline_decodificar(
        Pipeline *pipeline, PALAVRA p1_MBR, PALAVRA *p2_IR, PALAVRA *p2_MAR, BancoRegistradores *banco) {

    PALAVRA pc_execucao = banco->rPC;
    // check in
    banco->rMBR = p1_MBR;

    pipeline->f_decodificar(banco);
    pipeline->f_decodificar = NULL;

    if (banco->rIR == OP_STOR_R && rMAR_read(banco) == pc_execucao) {
        pipeline->flags |= CARREGAR_DIREITA;
        rIBR_reset(banco);
    }

    if (banco->rIR == OP_STOR_R || banco->rIR == OP_STOR_L) {
        pipeline_enfileirar_dep(pipeline, OP_STOR_R, banco->rMAR);
    }

    // check out
    *p2_IR  = banco->rIR;
    *p2_MAR = banco->rMAR;

    pipeline->f_busca_operandos = pipeline_get_instrucao(pipeline, banco->rIR).f_busca_operandos;
}

void pipeline_buscar_operandos(
        Pipeline *pipeline, PALAVRA p2_IR, PALAVRA p2_MAR, PALAVRA *p3_IR, PALAVRA *p3_MAR, PALAVRA *p3_MBR, BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {

    banco->rMAR = p2_MAR;

    pipeline->f_busca_operandos(banco, barramento, memoria);
    pipeline->f_busca_operandos = NULL;

    *p3_IR = p2_IR;
    *p3_MBR = banco->rMBR;
    *p3_MAR = banco->rMAR;

    pipeline->f_executar = pipeline_get_instrucao(pipeline, p2_IR).f_executar;
}

void pipeline_executar(
        Pipeline *pipeline, PALAVRA p3_IR, PALAVRA p3_MAR, PALAVRA p3_MBR, PALAVRA *p4_MAR, PALAVRA *p4_MBR, BancoRegistradores *banco, ULA *ula) {

    banco->rMAR = p3_MAR;
    banco->rMBR = p3_MBR;

    pipeline->f_executar(pipeline->ciclo_execucao++, banco, ula, &pipeline->flags);

    if (pipeline->flags & STOR_EXECUTADO) {
        PRINT("dependencia inclusa! (OP_STOR %ld)", rMAR_read(banco));
        pipeline_enfileirar_dep(pipeline, OP_STOR, rMAR_read(banco));
    }

    InstrucaoConfig inst = pipeline_get_instrucao(pipeline, p3_IR);
    if (pipeline->ciclo_execucao >= inst.tempo) {
        pipeline->ciclo_execucao = 0;
        pipeline->f_executar = NULL;

        *p4_MAR = banco->rMAR;
        *p4_MBR = banco->rMBR;

        pipeline->f_escrita_resultados = inst.f_escrita_resultados;
    }
}

void pipeline_escrita_resultados(
        Pipeline *pipeline, PALAVRA p4_MBR, PALAVRA p4_MAR, BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula) {

    banco->rMBR = p4_MBR;
    banco->rMAR = p4_MAR;

    pipeline->f_escrita_resultados(banco, barramento, memoria, ula, &pipeline->flags);
    pipeline->f_escrita_resultados = NULL;

    if (pipeline->flags & STOR_PARCIAL_FINALIZADO) {
        pipeline->flags &= ~STOR_PARCIAL_FINALIZADO;
        pipeline_unshift_dep(pipeline);
    }
}

void pipeline_flush(Pipeline *pipeline) {
    pipeline->ciclo_execucao = 0;

    pipeline->f_buscar_instrucao = NULL;
    pipeline->f_decodificar = NULL;
    pipeline->f_busca_operandos = NULL;
    pipeline->f_executar = NULL;
    pipeline->f_escrita_resultados = NULL;

    pipeline->flags &= ~PIPELINE_FLUSH;
}

void pipeline_enfileirar_dep(Pipeline *pipeline, INSTRUCAO op, ARGUMENTO posicao) {
    for (int i = 0; i < FILA_DEPENDENCIA_SIZE; i++) {
        if (pipeline->fila_dependencia[i].op == 0) {
            pipeline->fila_dependencia[i].op = op;
            pipeline->fila_dependencia[i].posicao = (int16_t)posicao;
            return;
        }
    }

    WARN("fila dependencias cheia!");
}

void pipeline_pop_dep(Pipeline *pipeline) {
    // int8_t pos;
    // for (
    //     pos = FILA_DEPENDENCIA_SIZE - 1;
    //     pos >= 0 && (pipeline->fila_dependencia[pos].op != op || pipeline->fila_dependencia[pos].posicao != posicao);
    //     pos--
    // );

    // if (pos < 0) return;

    // for (int i = pos; i < FILA_DEPENDENCIA_SIZE - 1; i++) {
    //     pipeline->fila_dependencia[i] = pipeline->fila_dependencia[i+1];
    //     pipeline->fila_dependencia[i + 1] = (NoDependencia){
    //         .op = 0
    //     };
    // }

    for (int i = FILA_DEPENDENCIA_SIZE - 1; i >= 0; i--) {
        if (pipeline->fila_dependencia[i].op != 0) {
            PRINT("FILA DEPENDENCIA POP (%s %d)", optoa(pipeline->fila_dependencia[i].op), pipeline->fila_dependencia[i].posicao);
            pipeline->fila_dependencia[i].op = 0;
            return;
        }
    }

    WARN("fila dependencia vazia");
}

void pipeline_unshift_dep(Pipeline *pipeline) {
    for (int i = 0; i < FILA_DEPENDENCIA_SIZE - 1; i++) {
        PRINT("fila dependencia unshift (%s %d)", optoa(pipeline->fila_dependencia[i].op), pipeline->fila_dependencia[i].posicao);
        pipeline->fila_dependencia[i] = pipeline->fila_dependencia[i + 1];
        pipeline->fila_dependencia[i + 1] = (NoDependencia){
            .op = 0,
            .posicao = 0
        };
    }
}

bool pipeline_checar_dep(Pipeline *pipeline, ARGUMENTO posicao, TipoDependencia tipo) {
    for (int i = 0; i < FILA_DEPENDENCIA_SIZE; i++) {
        NoDependencia no = pipeline->fila_dependencia[i];

        if (no.op != 0 && no.posicao == posicao) {
            PRINT("dependencia encontrada! (%s %d)", optoa(no.op), no.posicao);
            if ((tipo == STOR    && no.op == OP_STOR) ||
                (tipo == STOR_LR && (no.op == OP_STOR_R || no.op == OP_STOR_L))) {
                return true;
            }
        }
    }

    return false;
}