#ifndef BUSCAR_OPERANDOS_H_
#define BUSCAR_OPERANDOS_H_

#include <stdint.h>
#include "../../registradores/registradores.h"
#include "../../barramento/barramento.h"
#include "../../memoria/memoria.h"
#include "../../defs/defs.h"

void buscar_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);

#endif
