#ifndef MEMORIA_H_
#define MEMORIA_H_

#include "../defs.h"
#define TAMANHO 4096
#define TAMANHO_REAL TAMANHO * 5
#define TAMANHO_DADOS 500

#define PALAVRA long
#define INSTRUCAO char
#define ARGUMENTO short
#define MASK 0xFFFFFFFFFF
#define OP_MASK 0xFF
#define ARGUMENTO_MASK 0xFFF

typedef struct {
    // 4096 * 40
    // 4096 * 5 * 8
    char dados[TAMANHO_REAL];
} Memoria;

Memoria *memoria_criar(void);
void memoria_escrever(Memoria *mem, uint pos, PALAVRA pal);
PALAVRA memoria_ler(Memoria *mem, uint pos);
void adicionar_instrucao(Memoria *mem, INSTRUCAO op, ARGUMENTO arg, uint pos);

#endif