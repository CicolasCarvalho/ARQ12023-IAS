#ifndef DECODER_H_
#define DECODER_H_

#include "../defs.h"
#include "../memoria/memoria.h"
#include <stdio.h>  

void memoria_para_arquivo(FILE *file, Memoria *memoria);
void arquivo_para_memoria(FILE *file, Memoria *memoria);
void compilar_secao_dados(FILE *in, Memoria *mem);
void compilar_secao_programa(FILE *in, Memoria *mem);

#endif