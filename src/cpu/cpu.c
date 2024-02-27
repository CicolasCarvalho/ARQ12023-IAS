#include "./cpu.h"

CPU *CPU_criar(void) {
    CPU *cpu = malloc(sizeof(CPU));

    cpu->banco_regs = (BancoRegistradores){
        .rAC = 0,
        .rEQ = 0,
        .rMBR = 0,
        .rPC = 0,
        .rMAR = 0,
        .rIBR = 0,
        .rIR = 0,
    };

    return cpu;
}

// insercao em uma lista ligada
void CPU_inserir_tempo_operacao(CPU *cpu, INSTRUCAO op, short tempo) {
    // PRINT("op: %s tempo: %i", optoa(op), tempo);

    if (cpu->config.tempo_execucao_lista == NULL) {
        cpu->config.tempo_execucao_lista = PipelineConfig_criar(op, tempo);
        return;
    }

    PipelineOpConfigNode *tmp = cpu->config.tempo_execucao_lista;

    while (tmp->op != op && tmp->prox != NULL) {
        tmp = tmp->prox;
    }

    if (tmp->op == op) {
        tmp->tempo = tempo;
        return;
    }

    tmp->prox = PipelineConfig_criar(op, tempo);
}

short CPU_get_tempo_operacao(CPU *cpu, INSTRUCAO op) {
    if (cpu->config.tempo_execucao_lista == NULL) RAISE("CPU nao tem nenhuma configuração de pipeline");

    PipelineOpConfigNode *tmp = cpu->config.tempo_execucao_lista;

    while (tmp->op != op && tmp->prox != NULL) {
        tmp = tmp->prox;
    }

    if (tmp->op == op) return tmp->tempo;

    if (tmp == NULL) RAISE("CPU nao tem nenhuma configuração para '%d' de pipeline", op);
    return -1;
}

// -Pipeline-----------------------------------------------------------------------------------------------------------------

PipelineOpConfigNode *PipelineConfig_criar(INSTRUCAO op, short tempo) {
    PipelineOpConfigNode *pipeline_config = malloc(sizeof(PipelineOpConfigNode));

    pipeline_config->op = op;
    pipeline_config->tempo = tempo;

    return pipeline_config;
}