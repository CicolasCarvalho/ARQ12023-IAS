#ifndef BARRAMENTO_H_
#define BARRAMENTO_H_

#include <stdint.h>
#include <stdlib.h>
#include "../defs/defs.h"
#include "../registradores/registradores.h"

typedef enum {
    NENHUM,
    CARREGAR,
    GUARDAR
} FUNCAO_BARRAMENTO_CONTROLE;

typedef struct {
    FUNCAO_BARRAMENTO_CONTROLE controle;
    PALAVRA dados;
    PALAVRA endereco;
} Barramento;

Barramento *barramento_criar(void);
void barramento_free(Barramento *barramento);

void barramento_endereco_write(Barramento *barramento, PALAVRA pal);
PALAVRA barramento_endereco_read(Barramento *barramento);
void barramento_dados_write(Barramento *barramento, PALAVRA pal);
PALAVRA barramento_dados_read(Barramento *barramento);
void barramento_controle_set(Barramento *barramento, FUNCAO_BARRAMENTO_CONTROLE func);

#endif