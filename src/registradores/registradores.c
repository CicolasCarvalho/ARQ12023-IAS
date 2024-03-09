#include "./registradores.h"

void rPC_increment(BancoRegistradores *banco) {
    banco->rPC++;
}

void rIBR_reset(BancoRegistradores *banco) {
    banco->rIBR = 0;
}

void rAC_load(BancoRegistradores *banco, PALAVRA origem) {
    banco->rAC = origem;
}

void rMQ_load(BancoRegistradores *banco, PALAVRA origem) {
    banco->rMQ = origem;
}

void rMBR_load(BancoRegistradores *banco, PALAVRA origem) {
    banco->rMBR = origem;
}

void rPC_load(BancoRegistradores *banco, PALAVRA origem) {
    banco->rPC = origem;
}

void rMAR_load(BancoRegistradores *banco, PALAVRA origem, PALAVRA mask) {
    uint deslocamento = mask == LEFT_MASK ? 20 : 0;
    PALAVRA mask_real = ARGUMENTO_MASK << deslocamento;

    banco->rMAR = (origem & mask_real) >> (deslocamento);
}

void rIBR_load(BancoRegistradores *banco, PALAVRA origem) {
    banco->rIBR = origem & RIGHT_MASK;
}

void rIR_load(BancoRegistradores *banco, PALAVRA origem, PALAVRA mask) {
    uint deslocamento = mask == LEFT_MASK ? 20 : 0;
    PALAVRA mask_real = OP_MASK << deslocamento;

    banco->rIR = (origem & mask_real) >> (deslocamento + 12);
}

PALAVRA rMQ_read(BancoRegistradores *banco) {
    return banco->rMQ;
}

PALAVRA rMAR_read(BancoRegistradores *banco) {
    return banco->rMAR;
}

PALAVRA rPC_read(BancoRegistradores *banco) {
    return banco->rPC;
}

PALAVRA rMBR_read(BancoRegistradores *banco) {
    return banco->rMBR;
}

PALAVRA rAC_read(BancoRegistradores *banco) {
    return banco->rAC;
}
