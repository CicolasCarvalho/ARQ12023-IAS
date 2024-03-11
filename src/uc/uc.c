#include "./uc.h"

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
    PRINT("Tick!");

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

        if (uc->pipeline.flags & PIPELINE_FLUSH || uc->pipeline.flags & STOP) return;
    }

    static PALAVRA  p3_IR  = 0,
                    p3_MAR = 0,
                    p3_MBR = 0;

    if (uc->pipeline.f_executar && !uc->pipeline.f_escrita_resultados) {
        PRINT("-- Execucao --");
        PRINT("p3_IR: (%s)", optoa(p3_IR));
        pipeline_executar(&uc->pipeline, p3_IR, p3_MAR, p3_MBR, &p4_MAR, &p4_MBR, banco, ula);

        if (uc->pipeline.flags & PIPELINE_FLUSH || uc->pipeline.flags & STOP) return;
    }

    static PALAVRA  p2_IR  = 0,
                    p2_MAR = 0;

    if (uc->pipeline.f_busca_operandos && !uc->pipeline.f_executar) {
        PRINT("-- Busca de Operandos --");
        pipeline_buscar_operandos(&uc->pipeline, p2_IR, p2_MAR, &p3_IR, &p3_MBR, banco, barramento, memoria);
    }

    static PALAVRA  p1_MBR = 0;

    if (uc->pipeline.f_decodificar && !uc->pipeline.f_busca_operandos) {
        PRINT("-- Decodificar --");
        pipeline_decodificar(&uc->pipeline, p1_MBR, &p2_IR, &p2_MAR, banco);
    }

    if (uc->pipeline.f_buscar_instrucao && !uc->pipeline.f_decodificar) {
        PRINT("-- Busca de Instrucoes --");
        pipeline_buscar_instrucao(&uc->pipeline, &p1_MBR, banco, barramento, memoria);
    }
}
