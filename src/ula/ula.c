#include "./ula.h"

ULA *ULA_criar(void) {
    ULA *ula = malloc(sizeof(ULA));

    ula->saida = 0;
    ula->overflow = 0;

    return ula;
}

void ULA_free(ULA *ula) {
    free(ula);
}

void ULA_executar(ULA *ula, PALAVRA a, PALAVRA b, ULAControleEnum controle) {
    switch (controle) {
        case TRANSFERIR:
            ula->saida = a;
            break;
        case SOMAR:
            ula->saida = a + b;
            break;
        case SUBTRAIR:
            // todo: negar bit 40
            ula->saida = a - b;
            break;
        case MULTIPLICAR:
            // todo: saida para mq
            ula->saida = a * b;
            break;
        case DIVIDIR:
            // todo
            break;
        default:
            RAISE("Sinal de controle da ULA não reconhecido! (%i)", controle);
            break;
    }
}
