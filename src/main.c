#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "./tradutor/tradutor.h"

int main(int argc, char **argv) {
    if (argc <= 4) RAISE("Numero de argumentos incompativel");

    if (strcmp(argv[1], "-p") == 0) {
        char *in = argv[2];
        
        if (strcmp(argv[3], "-m") != 0) RAISE("comando não receonhecido '%s'", argv[3]);
        
        char *out = argv[4];

        // compilar_para_memoria(argv[2]);
        compilar_para_arquivo(in, out);
    } else {
        RAISE("comando não receonhecido '%s'", argv[1])
    }
    
    return 0;
}