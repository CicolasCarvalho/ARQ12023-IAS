#ifndef OP_STOR_L_H_
#define OP_STOR_L_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"

#define ADD_OP_STOR_L(pipeline) CONFIG_INSTRUCAO(pipeline, op_stor_l, OP_STOR_L)

void op_stor_l_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_stor_l_executar(int iteracao, BancoRegistradores *banco, ULA *ula);
void op_stor_l_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula);

#endif