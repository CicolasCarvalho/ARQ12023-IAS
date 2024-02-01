#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "defs/defs.h"
#include "tradutor/tradutor.h"

int main(int argc, char **argv) {
    // char *in = "./resources/in.ias";

    // FILE *f = fopen(in, "r");
    // if (!f) RAISE("Arquivo '%s' nao encontrado", in);

    // IAS *ias = IAS_criar();
    // Memoria *mem = memoria_criar(TAMANHO, 200);
    // ias->memoria = mem;
    // CPU *cpu = CPU_criar();
    // ias->cpu = cpu;

    // compilar_para_IAS(f, ias);

    // return 0;

    if (argc <= 4) RAISE("Numero de argumentos incompativel");

    if (strcmp(argv[1], "-p") == 0) {
        char *in = argv[2];

        FILE *f = fopen(in, "r");
        if (!f) RAISE("Arquivo '%s' nao encontrado", in);


        if (strcmp(argv[3], "-i") != 0) RAISE("comando nao receonhecido '%s'", argv[3]);
        int tamanho_dados = atoi(argv[4]);
        
        IAS *ias = IAS_criar();
        Memoria *mem = memoria_criar(TAMANHO, tamanho_dados);
        ias->memoria = mem;
        CPU *cpu = CPU_criar();
        ias->cpu = cpu;

        compilar_para_IAS(f, ias);
        // IAS bootloader
    } else if (strcmp(argv[1], "-t") == 0) {
        char *in = argv[2];
        
        if (strcmp(argv[3], "-m") != 0) RAISE("comando nao receonhecido '%s'", argv[3]);
        char *out = argv[4];

        if (strcmp(argv[5], "-i") != 0) RAISE("comando nao receonhecido '%s'", argv[5]);
        int tamanho_dados = atoi(argv[6]);

        compilar_para_arquivo(in, out, TAMANHO, tamanho_dados);
    } else {
        RAISE("comando nao receonhecido '%s'", argv[1])
    }
    
    return 0;
}