#if 0
#ifndef <NOME_DA_OPERACAO>_H_
#define <NOME_DA_OPERACAO>_H_

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "./defaults/buscar_operandos.h"

#define ADD_<NOME_DA_OPERACAO>(pipeline) CONFIG_INSTRUCAO(pipeline, <nome_da_operacao>, <NOME_DA_OPERACAO>)

void <nome_da_operacao>_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void <nome_da_operacao>_executar(int iteracao, BancoRegistradores *banco, ULA *ula);
void <nome_da_operacao>_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, ULA *ula);

#endif
#endif