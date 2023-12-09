#include "./decoder.h"

void memoria_para_arquivo(FILE *file, Memoria *memoria) {
    fwrite(memoria->dados, sizeof(char), TAMANHO_REAL, file);
}