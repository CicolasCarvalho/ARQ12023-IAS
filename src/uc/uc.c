#include "./uc.h"

UC *UC_criar(void) {
    UC *uc = malloc(sizeof(UC));

    uc->pipeline.f_buscar_instrucao = buscar_instrucao;
    uc->pipeline.f_decodificar = NULL;
    uc->pipeline.f_busca_operandos = NULL;
    uc->pipeline.f_executar = NULL;
    uc->pipeline.f_escrita_resultados = NULL;

    uc->pipeline.ciclo_execucao = 0;

    return uc;
}

void UC_free(UC *uc) {
    free(uc);
}

void UC_tick(UC *uc, ULA *ula, BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    PRINT("PC: %ld", (int64_t)banco->rPC);

    static PALAVRA  p4_MBR = 0,
                    p4_MAR = 0;

    if (uc->pipeline.f_escrita_resultados) {
        pipeline_escrita_resultados(&uc->pipeline, p4_MBR, p4_MAR, banco, barramento, memoria);
    }

    static PALAVRA  p3_IR  = 0;

    if (uc->pipeline.f_executar && !uc->pipeline.f_escrita_resultados) {
        pipeline_executar(&uc->pipeline, p3_IR, &p4_MAR, &p4_MBR, banco, ula);
    }

    static PALAVRA  p2_IR  = 0,
                    p2_MAR = 0;

    if (uc->pipeline.f_busca_operandos && !uc->pipeline.f_executar) {
        pipeline_buscar_operandos(&uc->pipeline, p2_IR, p2_MAR, &p3_IR, banco, barramento, memoria);
    }

    static PALAVRA  p1_MBR = 0;

    if (uc->pipeline.f_decodificar && !uc->pipeline.f_busca_operandos) {
        pipeline_decodificar(&uc->pipeline, p1_MBR, &p2_IR, &p2_MAR, banco);
    }

    if (uc->pipeline.f_buscar_instrucao && !uc->pipeline.f_decodificar) {
        pipeline_buscar_instrucao(&uc->pipeline, &p1_MBR, banco, barramento, memoria);
    }
}
