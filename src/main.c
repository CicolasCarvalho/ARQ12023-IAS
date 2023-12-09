#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "./compilador/compilador.h"

int main(int argc, char **argv) {
    if (argc <= 1) RAISE("Numero de argumentos incompativel");

    if (strcmp(argv[1], "--compile") == 0) {
        if (argc <= 2) RAISE("Necessario um caminho para compilar");

        // compilar_para_memoria(argv[2]);
        compilar_para_arquivo(argv[2], "./build/out.bin");
    } else {
        RAISE("comando não receonhecido '%s'", argv[1])
    }
    
    return 0;
}