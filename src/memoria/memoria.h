#ifndef MEMORIA_H_
#define MEMORIA_H_

#include <stdint.h>
#include "../defs/defs.h"
#include "../utils.h"

typedef struct {
    int tamanho;
    int tamanho_dados;
    // 4096 * 40
    // 4096 * 5 * 8
    uint8_t *dados;
} Memoria;

Memoria *memoria_criar(int tamanho, int tamanho_dados);
void memoria_escrever(Memoria *mem, uint pos, PALAVRA pal);
PALAVRA memoria_ler(Memoria *mem, uint pos);
void memoria_adicionar_instrucao(Memoria *mem, INSTRUCAO op, ARGUMENTO arg, uint pos);

#endif