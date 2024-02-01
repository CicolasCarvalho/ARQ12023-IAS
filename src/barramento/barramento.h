#ifndef BARRAMENTO_H_
#define BARRAMENTO_H_

#include <stdint.h>
#include "../defs/defs.h"

typedef struct {
    PALAVRA dados;
    PALAVRA endereco;
} Barramento;

#endif