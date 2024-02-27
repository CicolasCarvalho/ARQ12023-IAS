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

#endif