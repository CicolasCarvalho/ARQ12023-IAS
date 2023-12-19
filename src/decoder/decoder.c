#include "./decoder.h"

void memoria_para_arquivo(FILE *file, Memoria *memoria) {
    for (int i = 0; i < TAMANHO; i++) {
        PALAVRA pal = memoria_ler(memoria, i);

        fprintf(file, "%llu\n", pal);
    }
}