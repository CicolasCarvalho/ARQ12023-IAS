#ifndef OP_ADD_H_
#define OP_ADD_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"

#define ADD_OP_ADD(pipeline) CONFIG_INSTRUCAO(pipeline, op_add, OP_ADD)

void op_add_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_add_executar(int iteracao, BancoRegistradores *banco, ULA *ula);
void op_add_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula);

#endif