#include "./compilador.h"

void compilar_para_arquivo(char *in, char *out) {
    FILE *f = fopen(in, "r");
    if (!f) RAISE("Arquivo '%s' não encontrado", in);
    FILE *f_out = fopen(out, "w");
    if (!f_out) RAISE("Arquivo '%s' não encontrado", out);

    Memoria *mem = compilar_para_memoria(f);
    // escrever_memoria_arquivo(f_out, mem);

    fclose(f);
    fclose(f_out);
}