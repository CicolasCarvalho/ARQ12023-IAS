#ifndef TRADUTOR_H_
#define TRADUTOR_H_

#include "../defs/defs.h"
#include "../utils.h"
#include "../memoria/memoria.h"
#include "../ias/ias.h"
#include "../decoder/decoder.h"

void compilar_para_arquivo(char *in, char *out, int tamanho, int tamanho_dados);
void compilar_para_memoria(FILE *in, Memoria *mem);
void compilar_para_IAS(FILE *in, IAS *ias);

#endif