#include "./ias.h"

IAS *IAS_criar(void) {
    IAS *ias = malloc(sizeof(IAS));

    ias->config = (IASConfig){
        .rodando = false,
    };
    ias->cpu = NULL;
    ias->memoria = NULL;

    return ias;
}

void IAS_iniciar(IAS *ias, PALAVRA PC) {
    ias->config.rodando = true;
    ias->cpu->banco_regs.rPC = PC;
}

void IAS_tick(IAS *ias) {
    BancoRegistradores *banco_regs = &ias->cpu->banco_regs;
    PALAVRA PC_antigo = banco_regs->rPC;

    if (banco_regs->rIBR != 0) {
        rIR_load(banco_regs, banco_regs->rIBR, RIGHT_MASK);
        rMAR_load(banco_regs, banco_regs->rIBR, RIGHT_MASK);

        rIBR_reset(banco_regs);
        rPC_increment(banco_regs);
    } else {
        // MAR <- PC
        rMAR_load(banco_regs, banco_regs->rPC, RIGHT_MASK);

        // barramento.endereco <- MAR
        barramento_endereco_load(ias->barramento, banco_regs);
        // barramento.dados <- M(barramento.endereco)
        memoria_tick(ias->memoria, ias->barramento);
        // MBT <- barramento.dados
        barramento_dados_read(ias->barramento, banco_regs);

        if ((banco_regs->rMBR & LEFT_MASK) == 0) {

            rIR_load(banco_regs, banco_regs->rMBR, RIGHT_MASK);
            rMAR_load(banco_regs, banco_regs->rMBR, RIGHT_MASK);

            rPC_increment(banco_regs);
        } else {
            rIBR_load(banco_regs, banco_regs->rMBR);
            rIR_load(banco_regs, banco_regs->rMBR, LEFT_MASK);
            rMAR_load(banco_regs, banco_regs->rMBR, LEFT_MASK);
        }
    }

    PRINT("%ld: %s %ld", PC_antigo, optoa(banco_regs->rIR), banco_regs->rMAR);
}