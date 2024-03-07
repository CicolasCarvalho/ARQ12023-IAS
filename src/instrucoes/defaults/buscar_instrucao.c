#include "buscar_instrucao.h"

void buscar_instrucao(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
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