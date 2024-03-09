#ifndef ULA_H_
#define ULA_H_

#include <stdint.h>
#include "../defs/defs.h"

typedef enum {
    TRANSFERIR,
    SOMAR,
    SUBTRAIR,
    SUBTRAIR_MOD,
    MULTIPLICAR,
    DIVIDIR,
    SOMAR_MOD,
    MAIOR_IGUAL,
    NEGATIVO,
    NEGATIVO_MOD,
    MOD,
    LSH,
    RSH
} ULAControleEnum;

typedef struct {
    PALAVRA saida;
    PALAVRA overflow;
} ULA;

ULA *ULA_criar(void);
void ULA_free(ULA *ula);
void ULA_executar(ULA *ula, PALAVRA a, PALAVRA b, ULAControleEnum controle);

#endif