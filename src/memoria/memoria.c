#include "./memoria.h"

Memoria *memoria_criar(void) {
    Memoria *mem = malloc(sizeof(*mem));

    memset(mem->dados, 0b00000000, TAMANHO_REAL);

    return mem;
}