#ifndef OP_JUMP_R_H_
#define OP_JUMP_R_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"

#define ADD_OP_JUMP_R(pipeline) CONFIG_INSTRUCAO(pipeline, op_jump_r, OP_JUMP_R)

void op_jump_r_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_jump_r_executar(int iteracao, BancoRegistradores *banco, ULA *ula);
void op_jump_r_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula);

#endif