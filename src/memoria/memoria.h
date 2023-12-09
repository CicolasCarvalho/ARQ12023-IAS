#ifndef MEMORIA_H_
#define MEMORIA_H_

#include "../defs.h"
#define TAMANHO 4096
#define TAMANHO_REAL 4096 * 5
#define TAMANHO_DADOS 500

#define PALAVRA long
#define MASK 0xFFFFFFFFFF

typedef struct {
    // 4096 * 40
    // 4096 * 5 * 8
    char dados[TAMANHO_REAL];
} Memoria;

Memoria *memoria_criar(void);
void memoria_escrever(Memoria *mem, uint pos, PALAVRA pal);
PALAVRA memoria_ler(Memoria *mem, uint pos);

#endif