#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "utils.h"
#include "defs/defs.h"
#include "tradutor/tradutor.h"
#include "instrucoes/instrucoes.h"

#define CLOCK_SPEED 1000 // Hz
#define RODAR_SEM_CLOCK false

void clock_update(IAS *ias, int speed) {
    double tick_time = 1./speed,
           time_start,
           time_elapsed;
    struct timeval tv_start,
                   tv_elapsed;

    gettimeofday(&tv_start, NULL);
    time_start = ((double)tv_start.tv_usec / 1000000.) + ((double)tv_start.tv_sec);

    while (ias->config.rodando) {
        gettimeofday(&tv_elapsed, NULL);
        time_elapsed = ((double)tv_elapsed.tv_usec / 1000000.) + ((double)tv_elapsed.tv_sec);

        if (RODAR_SEM_CLOCK || (time_elapsed - time_start) > tick_time) {
            IAS_tick(ias);
            time_start = time_elapsed;
        }
    }
}

void configurar_instrucoes(CPU *cpu) {
    add_instrucoes(&cpu->uc->pipeline);
}

int main(int argc, char **argv) {
    if (argc <= 4) {
        RAISE("Numero de argumentos incompativel");
    }

    if (strcmp(argv[1], "-p") == 0) {
        char *in = argv[2];

        FILE *f = fopen(in, "r");
        if (!f) {
            RAISE("Arquivo '%s' nao encontrado", in);
        }

        if (strcmp(argv[3], "-i") != 0) {
            RAISE("comando nao receonhecido '%s'", argv[3]);
        }
        int tamanho_dados = atoi(argv[4]);

        Memoria *mem = memoria_criar(TAMANHO, tamanho_dados);
        CPU *cpu = CPU_criar();
        Barramento *barramento = barramento_criar();

        configurar_instrucoes(cpu);
        IAS *ias = IAS_criar(cpu, barramento, mem);

        compilar_para_IAS(f, ias);
        PRINT("compilado com sucesso!");
        
        IAS_iniciar(ias, tamanho_dados);
        clock_update(ias, CLOCK_SPEED);
        PRINT("Programa finalizado com sucesso!");

        FILE *f_out = fopen("build/out.ias.d", "w");
        if (!f_out) {
            RAISE("Arquivo '%s' não encontrado", "build/out.ias.d");
        }

        memoria_para_arquivo(f_out, mem);
        IAS_free(ias);
    } else if (strcmp(argv[1], "-t") == 0) {
        char *in = argv[2];
        
        if (strcmp(argv[3], "-m") != 0) {
            RAISE("comando nao receonhecido '%s'", argv[3]);
        }
        char *out = argv[4];

        if (strcmp(argv[5], "-i") != 0) {
            RAISE("comando nao receonhecido '%s'", argv[5]);
        }
        int tamanho_dados = atoi(argv[6]);

        compilar_para_arquivo(in, out, TAMANHO, tamanho_dados);
    } else {
        RAISE("comando nao receonhecido '%s'", argv[1]);
    }
    
    return 0;
}