#include "./ias.h"

IAS *IAS_criar(void) {
    IAS *ias = malloc(sizeof(IAS));

    ias->config = (IASConfig){};
    ias->memoria = NULL;

    return ias;
}