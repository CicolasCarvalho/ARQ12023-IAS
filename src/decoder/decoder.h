#ifndef DECODER_H_
#define DECODER_H_

#include <stdio.h>  
#include "../utils.h"
#include "../memoria/memoria.h"

void memoria_para_arquivo(FILE *file, Memoria *memoria);
void arquivo_para_memoria(FILE *file, Memoria *memoria);

#endif