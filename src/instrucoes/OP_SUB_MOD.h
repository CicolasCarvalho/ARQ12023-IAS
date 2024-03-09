#ifndef OP_SUB_MOD_H_
#define OP_SUB_MOD_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"
#include "../pipeline/pipeline.h"

#define ADD_OP_SUB_MOD(pipeline) CONFIG_INSTRUCAO(pipeline, op_sub_mod, OP_SUB_MOD)

void op_sub_mod_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_sub_mod_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags);
void op_sub_mod_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags);

#endif