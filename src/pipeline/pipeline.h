#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <stdint.h>
#include "../defs/defs.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "../ula/ula.h"
#include "../utils.h"
#include "../pipeline/pipeline.h"
#include "../instrucoes/defaults/decodificar.h"

#define FUN_BUSCA_INSTRUCAO(nome) \
    void (*nome)(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria)

#define FUN_DECODIFICAR(nome) \
    void (*nome)(BancoRegistradores *banco)

#define FUN_BUSCA_OPERANDOS(nome) \
    void (*nome)(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria)

#define FUN_EXECUCAO(nome) \
    void (*nome)(int iteracao, BancoRegistradores *banco, ULA *ula)

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
    uint8_t ciclo_execucao;

    FUN_BUSCA_INSTRUCAO(f_buscar_instrucao);
    FUN_DECODIFICAR(f_decodificar);
    FUN_BUSCA_OPERANDOS(f_busca_operandos);
    FUN_EXECUCAO(f_executar);
    FUN_ESCRITA_RESULTADOS(f_escrita_resultados);
} Pipeline;

void pipeline_inserir_tempo_operacao(Pipeline *pipeline, INSTRUCAO op, short tempo);
InstrucaoConfig pipeline_get_instrucao(Pipeline pipeline, INSTRUCAO op);
void pipeline_set_instrucao(Pipeline *pipeline, INSTRUCAO op,
                            FUN_BUSCA_OPERANDOS(f_busca_operandos),
                            FUN_EXECUCAO(f_executar),
                            FUN_ESCRITA_RESULTADOS(f_escrita_resultados));

void pipeline_buscar_instrucao(Pipeline *pipeline, PALAVRA *p1_MBR, BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void pipeline_decodificar(Pipeline *pipeline, PALAVRA p1_MBR, PALAVRA *p2_IR, PALAVRA *p2_MAR, BancoRegistradores *banco);
void pipeline_buscar_operandos(Pipeline *pipeline, PALAVRA p2_IR, PALAVRA p2_MAR, PALAVRA *p3_IR, BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void pipeline_executar(Pipeline *pipeline, PALAVRA p3_IR, PALAVRA *p4_MAR, PALAVRA *p4_MBR, BancoRegistradores *banco, ULA *ula);
void pipeline_escrita_resultados(Pipeline *pipeline, PALAVRA p4_MBR, PALAVRA p4_MAR, BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);

#endif
