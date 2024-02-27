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

    PRINT("%ld: %s %ld", banco_regs->rPC, optoa(banco_regs->rIR), banco_regs->rMAR);

    if (banco_regs->rIBR != 0) {
        banco_regs->rIR = (banco_regs->rIBR & (OP_MASK)) >> 12;
        banco_regs->rMAR = (banco_regs->rIBR & (ARGUMENTO_MASK));

        banco_regs->rIBR = 0;
        banco_regs->rPC += 1;
    } else {
        banco_regs->rMAR = banco_regs->rPC;
        
        // barramento_load_rMAR();
        ias->barramento->endereco = banco_regs->rMAR;
        // MEM_tick()
        ias->barramento->dados = memoria_ler(ias->memoria, ias->barramento->endereco);
        // barramento_set_rMBR();
        banco_regs->rMBR = ias->barramento->dados;

        if ((banco_regs->rMBR & LEFT_MASK) == 0) {
            banco_regs->rIR = (banco_regs->rMBR & OP_MASK) >> 12;
            banco_regs->rMAR = (banco_regs->rMBR & ARGUMENTO_MASK);

            banco_regs->rPC += 1;
        } else {
            banco_regs->rIBR = (banco_regs->rMBR & RIGHT_MASK);
            banco_regs->rIR = (banco_regs->rMBR & (OP_MASK << 20)) >> 32;
            banco_regs->rMAR = (banco_regs->rMBR & (ARGUMENTO_MASK << 20)) >> 20;
        }
    }
}