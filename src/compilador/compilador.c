#include "./compilador.h"

void compilar_para_arquivo(char *in, char *out) {
    FILE *f = fopen(in, "r");
    if (!f) RAISE("Arquivo '%s' não encontrado", in);
    FILE *f_out = fopen(out, "w");
    if (!f_out) RAISE("Arquivo '%s' não encontrado", out);

    Memoria *mem = compilar_para_memoria(f);
    memoria_para_arquivo(f_out, mem);

    fclose(f);
    fclose(f_out);
}

Memoria *compilar_para_memoria(FILE *in) {
    Memoria *mem = memoria_criar();

    compilar_secao_dados(in, mem);
    compilar_secao_programa(in, mem);

    return mem;
}

void compilar_secao_dados(FILE *in, Memoria *mem) {
    for (int i = 0; i < TAMANHO_DADOS; i++) {
        long dado = 0;
        if (fscanf(in, "%ld", &dado) == EOF) RAISE("Erro ao ler dado na posição %d", i);

        memoria_escrever(mem, i, dado);      
    }
    
}

void compilar_secao_programa(FILE *in, Memoria *mem) {
    char op[128] = "\0";
    int op_len = 0;
    char c = '\0';

    while ((c = fgetc(in)) != EOF) {
        if (c == '\n') {
            compilar_linha(op);
            op_len = 0;
            op[op_len] = '\0';
        } else if (c == ' ') {
            if (op_len > 0 && op[op_len - 1] != ' ') {
                op[op_len++] = ' ';
                op[op_len] = '\0';
            }
        } else {
            op[op_len++] = c;
            op[op_len] = '\0';
        }
    }
}

void compilar_linha(char *linha) {
    char *operacao = strtok(linha, " ");
    char *argumento = strtok(NULL, "\n");

    printf("Operacao: '%s' / '%s'\n", operacao, argumento);
}