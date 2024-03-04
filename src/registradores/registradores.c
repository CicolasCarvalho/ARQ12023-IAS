#include "./registradores.h"

void rPC_increment(BancoRegistradores *banco) {
    banco->rPC++;
}

void rIR_load(BancoRegistradores *banco, PALAVRA origem, PALAVRA mask) {
    uint deslocamento = mask == LEFT_MASK ? 20 : 0;
    PALAVRA mask_real = OP_MASK << deslocamento;

    banco->rIR = (origem & mask_real) >> (deslocamento + 12);
}

void rIBR_reset(BancoRegistradores *banco) {
    banco->rIBR = 0;
}

void rIBR_load(BancoRegistradores *banco, PALAVRA origem) {
    banco->rIBR = origem & RIGHT_MASK;
}

void rMAR_load(BancoRegistradores *banco, PALAVRA origem, PALAVRA mask) {
    uint deslocamento = mask == LEFT_MASK ? 20 : 0;
    PALAVRA mask_real = ARGUMENTO_MASK << deslocamento;

    banco->rMAR = (origem & mask_real) >> (deslocamento);
}

void rMBR_load(BancoRegistradores *banco, PALAVRA origem) {
    banco->rMBR = origem;
}