#ifndef DEFS_H_
#define DEFS_H_

#define TAMANHO 4096
// #define TAMANHO_REAL TAMANHO * 5
// int TAMANHO_DADOS = 500;

#define PALAVRA uint64_t
#define INSTRUCAO uint8_t
#define ARGUMENTO uint16_t
#define MASK (uint64_t)0xFFFFFFFFFF
#define OP_MASK (uint64_t)0xFF
#define ARGUMENTO_MASK (uint64_t)0xFFF

#define NUM_INSTRUCOES      22
#define OP_LSH              0b00010100 
#define OP_RSH              0b00010101
#define OP_LOAD             0b00000001
#define OP_STOR             0b00100001
#define OP_LOAD_MENOS       0b00000010
#define OP_LOAD_MOD         0b00000011
#define OP_LOAD_MENOS_MOD   0b00000100
#define OP_LOAD_MQ          0b00001010
#define OP_LOAD_MQ_M        0b00001001
#define OP_JUMP_L           0b00001101
#define OP_JUMP_R           0b00001110
#define OP_JUMP_COND_L      0b00001111
#define OP_JUMP_COND_R      0b00010000
#define OP_ADD              0b00000101
#define OP_ADD_MOD          0b00000111
#define OP_SUB              0b00000110
#define OP_SUB_MOD          0b00001000
#define OP_MUL              0b00001011
#define OP_DIV              0b00001100
#define OP_STOR_L           0b00010010
#define OP_STOR_R           0b00010011
#define OP_EXIT             0b11111111

#endif