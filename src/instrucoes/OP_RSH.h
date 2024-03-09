#ifndef OP_RSH_H_
#define OP_RSH_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"

#define ADD_OP_RSH(pipeline) CONFIG_INSTRUCAO(pipeline, op_rsh, OP_RSH)

void op_rsh_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_rsh_executar(int iteracao, BancoRegistradores *banco, ULA *ula);
void op_rsh_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula);

#endif