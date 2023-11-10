#ifndef UC_H_
#define UC_H_

#include <stdint.h>
#include "../defs/defs.h"

typedef struct {
    PALAVRA rPC;
    PALAVRA rMAR;
    PALAVRA rIBR;
    PALAVRA rIR;
} UC;

UC *UC_criar(void);

#endif