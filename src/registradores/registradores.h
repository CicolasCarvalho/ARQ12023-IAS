#ifndef REGISTRADORES_H_
#define REGISTRADORES_H_

#include <stdint.h>
#include "../defs/defs.h"

typedef struct {
    PALAVRA rAC;
    PALAVRA rMQ;
    PALAVRA rMBR;
    PALAVRA rPC;
    PALAVRA rMAR;
    PALAVRA rIBR;
    PALAVRA rIR;
} BancoRegistradores;

void rPC_increment(BancoRegistradores *banco);
void rIBR_reset(BancoRegistradores *banco);

void rAC_load(BancoRegistradores *banco, PALAVRA origem);
void rMQ_load(BancoRegistradores *banco, PALAVRA origem);
void rMBR_load(BancoRegistradores *banco, PALAVRA origem);
void rPC_load(BancoRegistradores *banco, PALAVRA origem);
void rMAR_load(BancoRegistradores *banco, PALAVRA origem, PALAVRA mask);
void rIBR_load(BancoRegistradores *banco, PALAVRA origem);
void rIR_load(BancoRegistradores *banco, PALAVRA origem, PALAVRA mask);

PALAVRA rMQ_read(BancoRegistradores *banco);
PALAVRA rMAR_read(BancoRegistradores *banco);
PALAVRA rPC_read(BancoRegistradores *banco);

#endif