#ifndef IAS_H_
#define IAS_H_

#include <stdint.h>
#include "../memoria/memoria.h"

typedef struct {
    // int tamanho;
    // int tamanho_dados;
} IASConfig;

typedef struct {
    IASConfig config;
    // CPU
    // Barramento
    Memoria *memoria;
} IAS;

IAS *IAS_criar(void);

#endif