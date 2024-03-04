#include "./barramento.h"

Barramento *barramento_criar(void) {
    Barramento *barramento = malloc(sizeof(Barramento));

    barramento->dados = 0;
    barramento->endereco = 0;

    return barramento;
}

void barramento_endereco_load(Barramento *barramento, BancoRegistradores *banco) {
    barramento->endereco = banco->rMAR;
}

void barramento_dados_load(Barramento *barramento, PALAVRA pal) {
    barramento->dados = pal;
}

void barramento_dados_read(Barramento *barramento, BancoRegistradores *banco) {
    // banco->rMBR = barramento->dados;
    rMBR_load(banco, barramento->dados);
}
