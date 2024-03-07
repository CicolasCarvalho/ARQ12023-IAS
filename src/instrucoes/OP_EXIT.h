#ifndef OP_EXIT_H_
#define OP_EXIT_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"

#define ADD_OP_EXIT(pipeline) CONFIG_INSTRUCAO(pipeline, op_exit, OP_EXIT)

void op_exit_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_exit_executar(int iteracao, BancoRegistradores *banco, ULA *ula);
void op_exit_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);

#endif
