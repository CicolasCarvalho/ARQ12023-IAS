#include "./uc.h"

static void buscar_instrucao(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
static void decodificar(BancoRegistradores *banco);

UC *UC_criar(void) {
    UC *uc = malloc(sizeof(UC));

    uc->pipeline.f_buscar_instrucao = buscar_instrucao;
    uc->pipeline.f_decodificar = decodificar;
    uc->pipeline.f_busca_operandos = NULL;
    uc->pipeline.f_executar = NULL;
    uc->pipeline.f_escrita_resultados = NULL;

    return uc;
}

void UC_tick(UC *uc, ULA *ula, BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    PALAVRA PC_antigo = banco->rPC;

    uc->pipeline.f_buscar_instrucao(banco, barramento, memoria);
    // check_out(0)
    // MBR
    // check_in(0)
    uc->pipeline.f_decodificar(banco);
    // check_out(1)
    // IR, IBR, MAR, MBR
    // check_in(1)
    // uc->pipeline.f_busca_operandos(banco, barramento, memoria);
    // check_out(2)
    // IR, IBR, MAR, MBR
    // check_in(2)
    // uc->pipeline.f_executar(0, banco, ula);
    // check_out(3)
    // IR, IBR, MAR, MBR, AC, MQ
    // check_in(3)
    // uc->pipeline.f_escrita_resultados(banco, barramento, memoria);

    PRINT("%ld: %s %ld", PC_antigo, optoa(banco->rIR), banco->rMAR);
}

//-Funcoes estaticas---------------------------------------------------------------------------------------------------------

static void buscar_instrucao(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    if (banco->rIBR == 0) {
        // MAR <- PC
        rMAR_load(banco, banco->rPC, RIGHT_MASK);

        // barramento.endereco <- MAR
        barramento_endereco_write(barramento, banco->rMAR);
        // barramento.dados <- M(barramento.endereco)
        barramento_controle_set(barramento, CARREGAR);
        memoria_tick(memoria, barramento);
        // MBT <- barramento.dados
        rMBR_load(banco, barramento_dados_read(barramento));
    }
}

static void decodificar(BancoRegistradores *banco) {
    if (banco->rIBR != 0) {
        rIR_load(banco, banco->rIBR, RIGHT_MASK);
        rMAR_load(banco, banco->rIBR, RIGHT_MASK);

        rIBR_reset(banco);
        rPC_increment(banco);
    } else {
        if ((banco->rMBR & LEFT_MASK) == 0) {
            rIR_load(banco, banco->rMBR, RIGHT_MASK);
            rMAR_load(banco, banco->rMBR, RIGHT_MASK);

            rPC_increment(banco);
        } else {
            rIBR_load(banco, banco->rMBR);
            rIR_load(banco, banco->rMBR, LEFT_MASK);
            rMAR_load(banco, banco->rMBR, LEFT_MASK);
        }
    }
}