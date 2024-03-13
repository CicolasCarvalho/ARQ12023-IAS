#include "decodificar.h"

void decodificar(BancoRegistradores *banco) {
    if (banco->rIBR == 0) {
        if ((banco->rMBR & LEFT_MASK) == 0) {
            rIR_load(banco, banco->rMBR, RIGHT_MASK);
            rMAR_load(banco, banco->rMBR, RIGHT_MASK);
            // PRINT("rIR: %ld - %s", banco->rIR, optoa(banco->rIR));
            // PRINT("rIBR: %ld - %s", banco->rIBR, optoa(banco->rIBR));
            // PRINT("rMBR: %ld - %s", banco->rMBR, optoa(banco->rMBR));

            rPC_increment(banco);
        } else {
            rIR_load(banco, banco->rMBR, LEFT_MASK);
            rMAR_load(banco, banco->rMBR, LEFT_MASK);

            // PRINT("rIR: %ld - %s", banco->rIR, optoa(banco->rIR));
            // PRINT("rIBR: %ld - %s", banco->rIBR, optoa(banco->rIBR));
            // PRINT("rMBR: %ld - %s", banco->rMBR, optoa(banco->rMBR));

            // if (banco->rIR == OP_STOR_R && rMAR_read(banco) == rPC_read(banco)) {
            //     *flag |= STOR_PARCIAL_EXECUTANDO;
            //     return;
            // }

            rIBR_load(banco, banco->rMBR);
        }
    } else {
        // PRINT("rIBR: %ld - %s", banco->rIBR, optoa(banco->rIBR));
        rIR_load(banco, banco->rIBR, RIGHT_MASK);
        rMAR_load(banco, banco->rIBR, RIGHT_MASK);

        rIBR_reset(banco);
        rPC_increment(banco);
    }
}