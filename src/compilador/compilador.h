#ifndef COMPILADOR_H_
#define COMPILADOR_H_

#include "../defs.h"
#include "../memoria/memoria.h"
#include "../decoder/decoder.h"

void compilar_para_arquivo(char *in, char *out);
Memoria *compilar_para_memoria(FILE *in);
void compilar_linha(char *linha);

#endif