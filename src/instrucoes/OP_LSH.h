#ifndef OP_LSH_H_
#define OP_LSH_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"

#define ADD_OP_LSH(pipeline) CONFIG_INSTRUCAO(pipeline, op_lsh, OP_LSH)

void op_lsh_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_lsh_executar(int iteracao, BancoRegistradores *banco, ULA *ula);
void op_lsh_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula);

#endif