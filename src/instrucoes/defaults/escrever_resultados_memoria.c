#include "escrever_resultados_memoria.h"

void escrever_resultados_memoria(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria) {
    // barramento.endereco <- MAR
    barramento_endereco_write(barramento, rMAR_read(banco));
    // barramento.dados <- M(barramento.endereco)
    barramento_controle_set(barramento, GUARDAR);
    memoria_tick(memoria, barramento);
}
