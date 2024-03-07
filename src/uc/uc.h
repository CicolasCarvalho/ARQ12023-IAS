#ifndef UC_H_
#define UC_H_

#include <stdint.h>
#include "../defs/defs.h"
#include "../memoria/memoria.h"
#include "../barramento/barramento.h"
#include "../ula/ula.h"
#include "../utils.h"
#include "../pipeline/pipeline.h"
#include "../instrucoes/defaults/buscar_instrucao.h"

typedef struct {
    Pipeline pipeline;
} UC;

UC *UC_criar(void);
void UC_free(UC *uc);

void UC_tick(UC *uc, ULA *ula, BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);

#endif