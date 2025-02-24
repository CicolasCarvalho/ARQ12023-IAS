#ifndef OP_JUMP_COND_L_H_
#define OP_JUMP_COND_L_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"

#define ADD_OP_JUMP_COND_L(pipeline) CONFIG_INSTRUCAO(pipeline, op_jump_cond_l, OP_JUMP_COND_L)

void op_jump_cond_l_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_jump_cond_l_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags);
void op_jump_cond_l_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags);

#endif