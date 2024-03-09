#ifndef OP_LOAD_MQ_M_H_
#define OP_LOAD_MQ_M_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"

#define ADD_OP_LOAD_MQ_M(pipeline) CONFIG_INSTRUCAO(pipeline, op_load_mq_m, OP_LOAD_MQ_M)

void op_load_mq_m_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void op_load_mq_m_executar(int iteracao, BancoRegistradores *banco, ULA *ula);
void op_load_mq_m_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula);

#endif