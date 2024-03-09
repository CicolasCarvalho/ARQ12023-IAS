#ifndef OP_STOR_R_H_
#define OP_STOR_R_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"
#include "./defaults/escrever_resultados_memoria.h"
#include "../pipeline/pipeline.h"

#define ADD_OP_STOR_R(pipeline) CONFIG_INSTRUCAO(pipeline, op_stor_r, OP_STOR_R)

void op_stor_r_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_stor_r_executar(int iteracao, BancoRegistradores *banco, ULA *ula, PipelineFlag *flags);
void op_stor_r_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula, PipelineFlag *flags);

#endif