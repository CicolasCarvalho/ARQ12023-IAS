#ifndef COMPILADOR_H_
#define COMPILADOR_H_

#include "../defs.h"
#include "../memoria/memoria.h"

void compilar_para_arquivo(char *in, char *out);
Memoria *compilar_para_memoria(char *in);

#endif