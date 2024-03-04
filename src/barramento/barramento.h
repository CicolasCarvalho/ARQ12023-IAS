#ifndef BARRAMENTO_H_
#define BARRAMENTO_H_

#include <stdint.h>
#include <stdlib.h>
#include "../defs/defs.h"
#include "../registradores/registradores.h"

typedef struct {
    PALAVRA dados;
    PALAVRA endereco;
} Barramento;

Barramento *barramento_criar(void);

void barramento_endereco_load(Barramento *barramento, BancoRegistradores *banco);
void barramento_dados_load(Barramento *barramento, PALAVRA pal);
void barramento_dados_read(Barramento *barramento, BancoRegistradores *banco);

#endif