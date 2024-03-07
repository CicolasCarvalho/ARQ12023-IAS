#if 0

#include "../utils.h"
#include "../defs/defs.h"
#include "../registradores/registradores.h"
#include "../uc/uc.h"
#include "../ula/ula.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"

#define ADD_<NOME_DA_OPERACAO>(pipeline) CONFIG_INSTRUCAO(pipeline, <nome_da_operacao>, <NOME_DA_OPERACAO>)

void <nome_da_operacao>_busca_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
void <nome_da_operacao>_executar(int iteracao, BancoRegistradores *banco, ULA *ula);
void <nome_da_operacao>_escrita_resultados(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);

#endif