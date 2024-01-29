#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "defs/defs.h"
#include "tradutor/tradutor.h"

int main(int argc, char **argv) {
    if (argc <= 4) RAISE("Numero de argumentos incompativel");

    if (strcmp(argv[1], "-p") == 0) {
        char *in = argv[2];

        FILE *f = fopen(in, "r");
        if (!f) RAISE("Arquivo '%s' não encontrado", in);

        IAS *ias = IAS_criar();

        if (strcmp(argv[3], "-i") != 0) RAISE("comando não receonhecido '%s'", argv[3]);
        int tamanho_dados = atoi(argv[4]);
        
        Memoria *mem = memoria_criar(TAMANHO, tamanho_dados);
        ias->memoria = mem;

        compilar_para_memoria(f, mem);
        // IAS bootloader
    } else if (strcmp(argv[1], "-t") == 0) {
        char *in = argv[2];
        
        if (strcmp(argv[3], "-m") != 0) RAISE("comando não receonhecido '%s'", argv[3]);
        char *out = argv[4];

        if (strcmp(argv[5], "-i") != 0) RAISE("comando não receonhecido '%s'", argv[5]);
        int tamanho_dados = atoi(argv[6]);

        compilar_para_arquivo(in, out, TAMANHO, tamanho_dados);
    } else {
        RAISE("comando não receonhecido '%s'", argv[1])
    }
    
    return 0;
}