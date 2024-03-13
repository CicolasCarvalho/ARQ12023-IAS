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
    int64_t a_i64 = i40toi64(a);
    int64_t b_i64 = i40toi64(b);

    switch (controle) {
        case TRANSFERIR:
            ula->saida = a;
            break;
        case SOMAR:
            ula->saida = i64toi40(a_i64 + b_i64);
            break;
        case SUBTRAIR:
            ula->saida = i64toi40(a_i64 - b_i64);
            break;
        case SUBTRAIR_MOD:
            ula->saida = i64toi40(a_i64 - b_i64);
            ula->saida &= MASK >> 1;
            break;
        case MULTIPLICAR: {
            // todo: saida de 80 bits
            PALAVRA mul = i64toi40(a_i64 * b_i64);
            ula->saida = mul & MASK;
            ula->overflow = mul & ~MASK;
            break;
        }
        case DIVIDIR:
            ula->saida = i64toi40(a_i64 / b_i64);
            ula->overflow = i64toi40(a_i64 % b_i64);
            break;
        case SOMAR_MOD:
            ula->saida = i64toi40(a_i64 + b_i64);
            ula->saida &= MASK >> 1;
            break;
        case MAIOR_IGUAL:
            ula->saida = i64toi40(a >= b);
            break;
        case NEGATIVO:
            ula->saida = a | (1ll << 39);
            break;
        case MOD:
            ula->saida = a & (MASK >> 1);
            break;
        case LSH:
            ula->saida = a << 1;
            break;
        case RSH:
            ula->saida = a >> 1;
            break;
        default:
            RAISE("Sinal de controle da ULA não reconhecido! (%i)", controle);
            break;
    }
}
