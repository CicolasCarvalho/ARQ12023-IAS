#include "./barramento.h"

Barramento *barramento_criar(void) {
    Barramento *barramento = malloc(sizeof(Barramento));

    barramento->dados = 0;
    barramento->endereco = 0;

    return barramento;
}