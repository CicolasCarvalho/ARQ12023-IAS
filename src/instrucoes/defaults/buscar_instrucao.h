#ifndef BUSCAR_INSTRUCAO_H_
#define BUSCAR_INSTRUCAO_H_

#include <stdint.h>
#include "../../registradores/registradores.h"
#include "../../barramento/barramento.h"
#include "../../memoria/memoria.h"
#include "../../defs/defs.h"

void buscar_instrucao(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);

#endif
