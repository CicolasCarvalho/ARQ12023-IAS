#ifndef REGISTRADORES_H_
#define REGISTRADORES_H_

#include <stdint.h>
#include "../defs/defs.h"

typedef struct {
    PALAVRA rAC;
    PALAVRA rEQ;
    PALAVRA rMBR;
    PALAVRA rPC;
    PALAVRA rMAR;
    PALAVRA rIBR;
    PALAVRA rIR;
} BancoRegistradores;

void rPC_increment(BancoRegistradores *banco);
void rIR_load(BancoRegistradores *banco, PALAVRA origem, PALAVRA mask);
void rIBR_reset(BancoRegistradores *banco);
void rIBR_load(BancoRegistradores *banco, PALAVRA origem);
void rMAR_load(BancoRegistradores *banco, PALAVRA origem, PALAVRA mask);
void rMBR_load(BancoRegistradores *banco, PALAVRA origem);

#endif