#include "./uc.h"

static bool possui_dependencia(Pipeline pipeline, ARGUMENTO posicao, PipelineFlag flag);

UC *UC_criar(void) {
    UC *uc = malloc(sizeof(UC));
    uc->pipeline.ciclo_execucao = 0;
    uc->pipeline.flags = PIPELINE_FLUSH;

    return uc;
}

void UC_free(UC *uc) {
    free(uc);
}

void UC_tick(UC *uc, ULA *ula, BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    static int count = 0;
    printf("\n");
    PRINT("Tick! (%i)", count++);

    if (uc->pipeline.flags & PIPELINE_FLUSH) {
        pipeline_flush(&uc->pipeline);
        PRINT("Pipeline vazio!");
        uc->pipeline.f_buscar_instrucao = buscar_instrucao;
    }

    static PALAVRA  p4_MBR = 0,
                    p4_MAR = 0;

    if (uc->pipeline.f_escrita_resultados) {
        PRINT("-- Escrita de resultados --");
        pipeline_escrita_resultados(&uc->pipeline, p4_MBR, p4_MAR, banco, barramento, memoria, ula);
        // PRINT("rPC: %s\n", optoa(p2_IR));

        if (uc->pipeline.flags & PIPELINE_FLUSH || uc->pipeline.flags & STOP) return;
    }

    static PALAVRA  p3_IR  = 0,
                    p3_MAR = 0,
                    p3_MBR = 0;

    if (uc->pipeline.f_executar && !uc->pipeline.f_escrita_resultados) {
        PRINT("-- Execucao --");
        PRINT("p3_IR: (%s)", optoa(p3_IR));
        PRINT("p3_MAR: (%ld)", p3_MAR);
        PRINT("p3_MBR: (%ld)", p3_MBR);
        PRINT("rAC: (%ld)", banco->rAC);
        pipeline_executar(&uc->pipeline, p3_IR, p3_MAR, p3_MBR, &p4_MAR, &p4_MBR, banco, ula);

        if (uc->pipeline.flags & PIPELINE_FLUSH || uc->pipeline.flags & STOP) return;
        if (uc->pipeline.flags & STOR_EXECUTADO) uc->pipeline.memoria_escrita = p3_MAR;
    }

    static PALAVRA  p2_IR  = 0,
                    p2_MAR = 0;

    if (uc->pipeline.f_busca_operandos && !uc->pipeline.f_executar && !possui_dependencia(uc->pipeline, p2_MAR, STOR_EXECUTADO)) {
        PRINT("-- Busca de Operandos --");
        PRINT("rPC: %s", optoa(p2_IR));
        pipeline_buscar_operandos(&uc->pipeline, p2_IR, p2_MAR, &p3_IR, &p3_MAR, &p3_MBR, banco, barramento, memoria);
    }

    static PALAVRA  p1_MBR = 0;

    if (uc->pipeline.f_decodificar && !uc->pipeline.f_busca_operandos) {
        PRINT("-- Decodificar --");
        pipeline_decodificar(&uc->pipeline, p1_MBR, &p2_IR, &p2_MAR, banco);
        PRINT("rPC: %s", optoa(banco->rIR));
    }

    if (uc->pipeline.f_buscar_instrucao && !uc->pipeline.f_decodificar && !possui_dependencia(uc->pipeline, rPC_read(banco), STOR_PARCIAL_EXECUTANDO)) {
        PRINT("-- Busca de Instrucoes --");
        PRINT("rPC: %ld", banco->rPC);
        pipeline_buscar_instrucao(&uc->pipeline, &p1_MBR, banco, barramento, memoria);
    }

    if (uc->pipeline.flags & STOR_EXECUTADO) uc->pipeline.flags &= ~STOR_EXECUTADO;
}

static bool possui_dependencia(Pipeline pipeline, ARGUMENTO posicao, PipelineFlag flag) {
    return (bool)(posicao == pipeline.memoria_escrita && (pipeline.flags & flag));
}
