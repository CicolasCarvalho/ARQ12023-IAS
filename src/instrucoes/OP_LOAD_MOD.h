#ifndef OP_LOAD_MOD_H_
#define OP_LOAD_MOD_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"

#define ADD_OP_LOAD_MOD(pipeline) CONFIG_INSTRUCAO(pipeline, op_load_mod, OP_LOAD_MOD)

void op_load_mod_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_load_mod_executar(int iteracao, BancoRegistradores *banco, ULA *ula);
void op_load_mod_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula);

#endif