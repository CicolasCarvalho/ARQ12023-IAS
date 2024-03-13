#include "escrever_resultados_memoria.h"

void escrever_resultados_memoria(BancoRegistradores *banco, Barramento *barramento, Memoria *memoria, PALAVRA mask) {
    FUNCAO_BARRAMENTO_CONTROLE funcao;
    if (mask == MASK) {
        barramento_dados_write(barramento, rMBR_read(banco));
        funcao = GUARDAR;
    }
    else if (mask == LEFT_MASK) {
        barramento_dados_write(barramento, (rMBR_read(banco) << 20) & LEFT_MASK);
        funcao = GUARDAR_PARCIAL_L;
    }
    else if (mask == RIGHT_MASK) {
        barramento_dados_write(barramento, rMBR_read(banco) & RIGHT_MASK);
        funcao = GUARDAR_PARCIAL_R;
    }
    else { RAISE("mascara desconhecida! (%lx)", mask); }

    barramento_endereco_write(barramento, rMAR_read(banco));
    barramento_controle_set(barramento, funcao);
    memoria_tick(memoria, barramento);
}
