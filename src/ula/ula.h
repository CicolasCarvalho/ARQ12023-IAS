#ifndef ULA_H_
#define ULA_H_

#include <stdint.h>
#include "../defs/defs.h"

typedef enum {
    TRANSFERIR,
    SOMAR,
    SUBTRAIR,
    MULTIPLICAR,
    DIVIDIR,
    SOMAR_MOD
} ULAControleEnum;

typedef struct {
    PALAVRA saida;
    PALAVRA overflow;
} ULA;

ULA *ULA_criar(void);
void ULA_executar(ULA *ula, PALAVRA a, PALAVRA b, ULAControleEnum controle);

#endif