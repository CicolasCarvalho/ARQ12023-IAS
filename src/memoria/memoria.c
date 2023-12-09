#include "./memoria.h"

Memoria *memoria_criar(void) {
    Memoria *mem = malloc(sizeof(*mem));

    memset(mem->dados, 0b00000000, TAMANHO_REAL);

    return mem;
}

void memoria_escrever(Memoria *mem, uint pos, PALAVRA pal) {
    if (pos >= TAMANHO) RAISE("'%d' nao é uma posicao valida", pos);

    uint relative = pos * 5;

    mem->dados[relative]     = (pal & 0xFF00000000) >> 32; // 0xFF = 0b11111111
    mem->dados[relative + 1] = (pal & 0x00FF000000) >> 24; 
    mem->dados[relative + 2] = (pal & 0x0000FF0000) >> 16; 
    mem->dados[relative + 3] = (pal & 0x000000FF00) >> 8; 
    mem->dados[relative + 4] =  pal & 0x00000000FF;
}

PALAVRA memoria_ler(Memoria *mem, uint pos) {
    if (pos >= TAMANHO) RAISE("'%d' nao é uma posicao valida", pos);

    uint relative = pos * 5;

    PALAVRA pal = 
        (PALAVRA)mem->dados[relative]     << 32 | 
        (PALAVRA)mem->dados[relative + 1] << 24 |
        (PALAVRA)mem->dados[relative + 2] << 16 |
        (PALAVRA)mem->dados[relative + 3] << 8  |
        (PALAVRA)mem->dados[relative + 4]       ;
    
    return pal;
}