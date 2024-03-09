#ifndef OP_MUL_H_
#define OP_MUL_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"

#define ADD_OP_MUL(pipeline) CONFIG_INSTRUCAO(pipeline, op_mul, OP_MUL)

void op_mul_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_mul_executar(int iteracao, BancoRegistradores *banco, ULA *ula);
void op_mul_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula);

#endif