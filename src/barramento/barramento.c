#include "./barramento.h"

Barramento *barramento_criar(void) {
    Barramento *barramento = malloc(sizeof(Barramento));

    barramento->controle = NENHUM;
    barramento->dados = 0;
    barramento->endereco = 0;

    return barramento;
}

void barramento_endereco_write(Barramento *barramento, PALAVRA pal) {
    barramento->endereco = pal;
}

PALAVRA barramento_endereco_read(Barramento *barramento) {
    return barramento->endereco;
}

void barramento_dados_write(Barramento *barramento, PALAVRA pal) {
    barramento->dados = pal;
}

PALAVRA barramento_dados_read(Barramento *barramento) {
    // banco->rMBR = barramento->dados;
    // rMBR_load(banco, barramento->dados);
    return barramento->dados;
}

void barramento_controle_set(Barramento *barramento, FUNCAO_BARRAMENTO_CONTROLE func) {
    barramento->controle = func;
}
