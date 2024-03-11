#include "./memoria.h"

Memoria *memoria_criar(int tamanho, int tamanho_dados) {
    Memoria *mem = malloc(sizeof(Memoria));

    mem->tamanho = tamanho;
    mem->tamanho_dados = tamanho_dados;
    mem->dados = calloc(tamanho * 5, sizeof(mem->dados));

    return mem;
}

void memoria_free(Memoria *mem) {
    free(mem->dados);
    free(mem);
}

void memoria_escrever(Memoria *mem, uint pos, PALAVRA pal, PALAVRA mask) {
    // if (pos >= TAMANHO) RAISE("'%d' nao é uma posicao valida", pos);

    uint relativo = pos * 5;

    mem->dados[relativo]     = (pal & 0xFF00000000 & mask) >> 32; // 0xFF = 0b11111111
    mem->dados[relativo + 1] = (pal & 0x00FF000000 & mask) >> 24;
    mem->dados[relativo + 2] = (pal & 0x0000FF0000 & mask) >> 16;
    mem->dados[relativo + 3] = (pal & 0x000000FF00 & mask) >>  8;
    mem->dados[relativo + 4] = (pal & 0x00000000FF & mask)      ;
}

PALAVRA memoria_ler(Memoria *mem, uint pos, PALAVRA mask) {
    // if (pos >= TAMANHO) RAISE("'%d' nao é uma posicao valida", pos);

    uint relativo = pos * 5;

    PALAVRA pal = 
        ((PALAVRA)mem->dados[relativo]    ) << 32 | 
        ((PALAVRA)mem->dados[relativo + 1]) << 24 |
        ((PALAVRA)mem->dados[relativo + 2]) << 16 |
        ((PALAVRA)mem->dados[relativo + 3]) << 8  |
        ((PALAVRA)mem->dados[relativo + 4])       ;
    
    return pal & mask;
}

void memoria_adicionar_instrucao(Memoria *mem, INSTRUCAO op, ARGUMENTO arg, uint pos) {
    PALAVRA pal = memoria_ler(mem, pos, MASK);
    PALAVRA operacao_argumento = (PALAVRA)op << 12 | (PALAVRA)arg;
    
    if ((pal & RIGHT_MASK) != 0)
        pal <<= 20;

    pal |= operacao_argumento;

    // pal = pal | (operacao_argumento << ((contador_operacoes % 2 == 0) * 20));
    
    memoria_escrever(mem, pos, pal, MASK);
}

void memoria_tick(Memoria *mem, Barramento *barramento) {
    PALAVRA mask = MASK;
    if (barramento->controle == GUARDAR_PARCIAL_L)
        mask = LEFT_MASK;
    if (barramento->controle == GUARDAR_PARCIAL_R)
        mask = RIGHT_MASK;

    switch (barramento->controle) {
        case NENHUM: {
            WARN("mamoria_tick() chamada com barramento.controle = 'NENHUM'");
            break;
        }
        case CARREGAR: {
            PALAVRA pal = memoria_ler(mem, barramento_endereco_read(barramento), mask);
            barramento_dados_write(barramento, pal);
            break;
        }
        case GUARDAR_PARCIAL_L:
        case GUARDAR_PARCIAL_R:
        case GUARDAR: {
            PALAVRA pal = barramento_dados_read(barramento);
            memoria_escrever(mem, barramento_endereco_read(barramento), pal, mask);
            break;
        }
        default:
            RAISE("barramento de controle possui um valor não suportado! (%i)", barramento->controle);
            break;
    }
}