#include "buscar_operandos.h"

void buscar_operandos(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    // barramento.endereco <- MAR
    barramento_endereco_write(barramento, rMAR_read(banco));
    // barramento.dados <- M(barramento.endereco)
    barramento_controle_set(barramento, CARREGAR);
    memoria_tick(memoria, barramento);
    // MBT <- barramento.dados
    rMBR_load(banco, barramento_dados_read(barramento));
}