#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <stdint.h>
#include "../defs/defs.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "../ula/ula.h"
#include "../utils.h"
#include "../pipeline/pipeline.h"

#define FUN_BUSCA_INSTRUCAO(nome) \
    void (*nome)(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria)

#define FUN_DECODIFICAR(nome) \
    void (*nome)(BancoRegistradores *banco)

#define FUN_BUSCA_OPERANDOS(nome) \
    void (*nome)(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria)

#define FUN_EXECUCAO(nome) \
    bool (*nome)(int iteracao, BancoRegistradores *banco, ULA *ula)

#define FUN_ESCRITA_RESULTADOS(nome) \
    void (*nome)(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria)

typedef struct {
    short tempo;
    FUN_BUSCA_OPERANDOS(f_busca_operandos);
    FUN_EXECUCAO(f_executar);
    FUN_ESCRITA_RESULTADOS(f_escrita_resultados);
} InstrucaoConfig;

typedef struct {
    InstrucaoConfig instrucoes[OP_STOR + 1];
    FUN_BUSCA_INSTRUCAO(f_buscar_instrucao);
    FUN_DECODIFICAR(f_decodificar);
    FUN_BUSCA_OPERANDOS(f_busca_operandos);
    FUN_EXECUCAO(f_executar);
    FUN_ESCRITA_RESULTADOS(f_escrita_resultados);

    uint8_t ciclo_execucao;
} Pipeline;

void pipeline_inserir_tempo_operacao(Pipeline *pipeline, INSTRUCAO op, short tempo);
InstrucaoConfig pipeline_get_instrucao(Pipeline pipeline, INSTRUCAO op);
void pipeline_set_instrucao(Pipeline *pipeline, INSTRUCAO op,
                            FUN_BUSCA_OPERANDOS(f_busca_operandos),
                            FUN_EXECUCAO(f_executar),
                            FUN_ESCRITA_RESULTADOS(f_escrita_resultados));


#endif
