#include "./decoder.h"

void memoria_para_arquivo(FILE *file, Memoria *memoria) {
    for (int i = 0; i < TAMANHO; i++) {
        PALAVRA pal = memoria_ler(memoria, i);

        if (i < TAMANHO_DADOS && (pal >> 39)) {
            long numero = pal & (MASK >> 1);
            numero |= 1ll << 63;
            
            fprintf(file, "-%lli\n", llabs(numero));
        } else {
            fprintf(file, "%llu\n", pal);
        }
    }
}