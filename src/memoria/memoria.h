#ifndef MEMORIA_H_
#define MEMORIA_H_

#include "../defs.h"
#define TAMANHO 4096
#define TAMANHO_REAL 4096 * 5

typedef struct {
    // 4096 * 40
    // 4096 * 5 * 8
    char dados[TAMANHO_REAL];
} Memoria;

Memoria *memoria_criar(void);

#endif