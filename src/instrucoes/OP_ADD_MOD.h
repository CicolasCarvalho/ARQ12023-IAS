#ifndef OP_ADD_MOD_H_
#define OP_ADD_MOD_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"

#define ADD_OP_ADD_MOD(pipeline) CONFIG_INSTRUCAO(pipeline, op_add_mod, OP_ADD_MOD)

void op_add_mod_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_add_mod_executar(int iteracao, BancoRegistradores *banco, ULA *ula);
void op_add_mod_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula);

#endif