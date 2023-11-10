#include "./decoder.h"

void memoria_para_arquivo(FILE *file, Memoria *memoria) {
    for (int i = 0; i < memoria->tamanho; i++) {
        PALAVRA pal = memoria_ler(memoria, i);

        fprintf(file, "%lu\n", pal);
    }
}