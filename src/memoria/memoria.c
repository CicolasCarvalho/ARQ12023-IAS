#include "./memoria.h"

Memoria *memoria_criar(int tamanho, int tamanho_dados) {
    Memoria *mem = malloc(sizeof(Memoria));

    mem->tamanho = tamanho;
    mem->tamanho_dados = tamanho_dados;
    mem->dados = malloc(tamanho * 5);
    memset(mem->dados, 0b00000000, tamanho * 5);

    return mem;
}

void memoria_escrever(Memoria *mem, uint pos, PALAVRA pal) {
    // if (pos >= TAMANHO) RAISE("'%d' nao � uma posicao valida", pos);

    uint relativo = pos * 5;

    mem->dados[relativo]     = (pal & 0xFF00000000) >> 32; // 0xFF = 0b11111111
    mem->dados[relativo + 1] = (pal & 0x00FF000000) >> 24; 
    mem->dados[relativo + 2] = (pal & 0x0000FF0000) >> 16; 
    mem->dados[relativo + 3] = (pal & 0x000000FF00) >>  8; 
    mem->dados[relativo + 4] = (pal & 0x00000000FF)      ;
}

PALAVRA memoria_ler(Memoria *mem, uint pos) {
    // if (pos >= TAMANHO) RAISE("'%d' nao � uma posicao valida", pos);

    uint relativo = pos * 5;

    PALAVRA pal = 
        ((PALAVRA)mem->dados[relativo]    ) << 32 | 
        ((PALAVRA)mem->dados[relativo + 1]) << 24 |
        ((PALAVRA)mem->dados[relativo + 2]) << 16 |
        ((PALAVRA)mem->dados[relativo + 3]) << 8  |
        ((PALAVRA)mem->dados[relativo + 4])       ;
    
    return pal;
}

void adicionar_instrucao(Memoria *mem, INSTRUCAO op, ARGUMENTO arg, uint pos) {
    static int contador_operacoes = 0;

    PALAVRA pal = memoria_ler(mem, pos);
    PALAVRA operacao_argumento = (PALAVRA)op << 12 | (PALAVRA)arg;
    
    pal = pal | (operacao_argumento << ((contador_operacoes % 2 == 0) * 20));
    
    memoria_escrever(mem, pos, pal);
    contador_operacoes++;
}