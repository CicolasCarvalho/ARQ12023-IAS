#ifndef ESCREVER_RESULTADOS_MEMORIA_H_
#define ESCREVER_RESULTADOS_MEMORIA_H_

#include <stdint.h>
#include "../../registradores/registradores.h"
#include "../../barramento/barramento.h"
#include "../../memoria/memoria.h"
#include "../../defs/defs.h"

void escrever_resultados_memoria(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, PALAVRA mask);

#endif
