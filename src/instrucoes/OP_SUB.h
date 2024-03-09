#ifndef OP_SUB_H_
#define OP_SUB_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"

#define ADD_OP_SUB(pipeline) CONFIG_INSTRUCAO(pipeline, op_sub, OP_SUB)

void op_sub_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_sub_executar(int iteracao, BancoRegistradores *banco, ULA *ula);
void op_sub_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula);

#endif