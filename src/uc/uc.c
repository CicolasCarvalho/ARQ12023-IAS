#include "./uc.h"

static void buscar_instrucao(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria);
static void decodificar(BancoRegistradores *banco);
static void check_in(Pipeline *pipeline, BancoRegistradores *banco, uint8_t estagio);
static void check_out(Pipeline *pipeline, BancoRegistradores *banco, uint8_t estagio);

UC *UC_criar(void) {
    UC *uc = malloc(sizeof(UC));

    uc->pipeline.f_buscar_instrucao = buscar_instrucao;
    uc->pipeline.f_decodificar = decodificar;
    uc->pipeline.f_busca_operandos = NULL;
    uc->pipeline.f_executar = NULL;
    uc->pipeline.f_escrita_resultados = NULL;

    uc->pipeline.ciclo_execucao = 0;

    return uc;
}

void UC_tick(UC *uc, ULA *ula, BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    PALAVRA PC_antigo = banco->rPC;

    uc->pipeline.f_buscar_instrucao(banco, barramento, memoria);
    uc->pipeline.f_decodificar(banco);

    InstrucaoConfig inst = pipeline_get_instrucao(uc->pipeline, banco->rIR & 0xFF);
    uc->pipeline.f_busca_operandos = inst.f_busca_operandos;
    if (uc->pipeline.f_busca_operandos) {
        uc->pipeline.f_busca_operandos(banco, barramento, memoria);
    }

    if (banco->rIR == OP_EXIT) exit(0);
    uc->pipeline.f_executar = inst.f_executar;
    if (uc->pipeline.f_executar) {
        uc->pipeline.f_executar(uc->pipeline.ciclo_execucao, banco, ula);
    }

    uc->pipeline.f_escrita_resultados = inst.f_escrita_resultados;
    if (uc->pipeline.f_escrita_resultados) {
        uc->pipeline.f_escrita_resultados(banco, barramento, memoria);
    }

    // if (uc->pipeline.f_escrita_resultados) {
    //     // ver se tem mid_registers[3]
    //     // se sim tem que fazer check_in(3)
    //     uc->pipeline.f_escrita_resultados(banco, barramento, memoria);
    //     uc->pipeline.f_escrita_resultados = NULL;
    // }
    //
    // if (uc->pipeline.f_executar) {
    //     // ver se tem mid_register[2]
    //     // se sim tem que fazer check_in(2)
    //     bool resultado = uc->pipeline.f_executar(uc->pipeline.ciclo_execucao, banco, ula);
    //
    //     if (resultado == true) {
    //         uc->pipeline.ciclo_execucao = 0;
    //     } else {
    //         uc->pipeline.ciclo_execucao++;
    //     }
    //     // fazer check_out(3)
    // }
    //
    // if (uc->pipeline.f_busca_operandos) {
    //    // ver se tem mid_registers[1]
    //    // se sim tem que fazer check_in(0)
    //    uc->pipeline.f_busca_operandos(banco, barramento, memoria);
    // }
    //
    // if (uc->pipeline.f_decodificar) {
    //     uc->pipeline.f_decodificar(banco);
    // }

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

static void check_in(Pipeline *pipeline, BancoRegistradores *banco, uint8_t estagio) {

}

static void check_out(Pipeline *pipeline, BancoRegistradores *banco, uint8_t estagio) {

}