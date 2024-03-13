#include "decodificar.h"

void decodificar(BancoRegistradores *banco) {
    if (banco->rIBR == 0) {
        if ((banco->rMBR & LEFT_MASK) == 0) {
            rIR_load(banco, banco->rMBR, RIGHT_MASK);
            rMAR_load(banco, banco->rMBR, RIGHT_MASK);

            rPC_increment(banco);
        } else {
            rIR_load(banco, banco->rMBR, LEFT_MASK);
            rMAR_load(banco, banco->rMBR, LEFT_MASK);

            rIBR_load(banco, banco->rMBR);
        }
    } else {
        rIR_load(banco, banco->rIBR, RIGHT_MASK);
        rMAR_load(banco, banco->rIBR, RIGHT_MASK);

        rIBR_reset(banco);
        rPC_increment(banco);
    }
}