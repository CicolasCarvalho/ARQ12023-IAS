#ifndef OP_LOAD_MENOS_H_
#define OP_LOAD_MENOS_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"
#include "../pipeline/pipeline.h"

#define ADD_OP_LOAD_MENOS(pipeline) CONFIG_INSTRUCAO(pipeline, op_load_menos, OP_LOAD_MENOS)

void op_load_menos_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_load_menos_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags);
void op_load_menos_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags);

#endif