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
    // if (pos >= TAMANHO) RAISE("'%d' nao é uma posicao valida", pos);

    uint relativo = pos * 5;

    mem->dados[relativo]     = (pal & 0xFF00000000) >> 32; // 0xFF = 0b11111111
    mem->dados[relativo + 1] = (pal & 0x00FF000000) >> 24; 
    mem->dados[relativo + 2] = (pal & 0x0000FF0000) >> 16; 
    mem->dados[relativo + 3] = (pal & 0x000000FF00) >>  8; 
    mem->dados[relativo + 4] = (pal & 0x00000000FF)      ;
}

PALAVRA memoria_ler(Memoria *mem, uint pos) {
    // if (pos >= TAMANHO) RAISE("'%d' nao é uma posicao valida", pos);

    uint relativo = pos * 5;

    PALAVRA pal = 
        ((PALAVRA)mem->dados[relativo]    ) << 32 | 
        ((PALAVRA)mem->dados[relativo + 1]) << 24 |
        ((PALAVRA)mem->dados[relativo + 2]) << 16 |
        ((PALAVRA)mem->dados[relativo + 3]) << 8  |
        ((PALAVRA)mem->dados[relativo + 4])       ;
    
    return pal;
}

void memoria_adicionar_instrucao(Memoria *mem, INSTRUCAO op, ARGUMENTO arg, uint pos) {
    PALAVRA pal = memoria_ler(mem, pos);
    PALAVRA operacao_argumento = (PALAVRA)op << 12 | (PALAVRA)arg;
    
    if ((pal & RIGHT_MASK) != 0)
        pal <<= 20;

    pal |= operacao_argumento;

    // pal = pal | (operacao_argumento << ((contador_operacoes % 2 == 0) * 20));
    
    memoria_escrever(mem, pos, pal);
}

void memoria_tick(Memoria *mem, Barramento *barramento) {
    if (barramento->controle == CARREGAR) {
        PALAVRA pal = memoria_ler(mem, barramento_endereco_read(barramento));
        barramento_dados_write(barramento, pal);
    } else if (barramento->controle == GUARDAR) {
        PALAVRA pal = barramento_dados_read(barramento);
        memoria_escrever(mem, barramento_endereco_read(barramento), pal);
    } else {
        RAISE("barramento de controle possui um valor não suportado! (%i)", barramento->controle);
    }
}