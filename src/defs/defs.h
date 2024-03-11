#ifndef DEFS_H_
#define DEFS_H_

#include "../utils.h"
#include <stdint.h>
#include <stdlib.h>

#define TAMANHO 4096
// #define TAMANHO_REAL TAMANHO * 5
// int TAMANHO_DADOS = 500;

// TODO: Mudar para uma implementação mais fidedigna quanto aos tamanhos
#define PALAVRA uint64_t
#define INSTRUCAO uint8_t
#define ARGUMENTO uint16_t
#define MASK (uint64_t)0xFFFFFFFFFF
#define OP_MASK (uint64_t)0xFF000
#define ARGUMENTO_MASK (uint64_t)0xFFF
#define LEFT_MASK (uint64_t)0xFFFFF00000
#define RIGHT_MASK (uint64_t)0x00000FFFFF

#define NUM_INSTRUCOES      22
#define OP_LSH              (INSTRUCAO)0b00010100
#define OP_RSH              (INSTRUCAO)0b00010101
#define OP_LOAD             (INSTRUCAO)0b00000001
#define OP_STOR             (INSTRUCAO)0b00100001
#define OP_LOAD_MENOS       (INSTRUCAO)0b00000010
#define OP_LOAD_MOD         (INSTRUCAO)0b00000011
#define OP_LOAD_MENOS_MOD   (INSTRUCAO)0b00000100
#define OP_LOAD_MQ          (INSTRUCAO)0b00001010
#define OP_LOAD_MQ_M        (INSTRUCAO)0b00001001

#define OP_JUMP_L           (INSTRUCAO)0b00001101
#define OP_JUMP_R           (INSTRUCAO)0b00001110

#define OP_JUMP_COND_L      (INSTRUCAO)0b00001111
#define OP_JUMP_COND_R      (INSTRUCAO)0b00010000

#define OP_ADD              (INSTRUCAO)0b00000101
#define OP_ADD_MOD          (INSTRUCAO)0b00000111
#define OP_SUB              (INSTRUCAO)0b00000110
#define OP_SUB_MOD          (INSTRUCAO)0b00001000
#define OP_MUL              (INSTRUCAO)0b00001011
#define OP_DIV              (INSTRUCAO)0b00001100

#define OP_STOR_L           (INSTRUCAO)0b00010010
#define OP_STOR_R           (INSTRUCAO)0b00010011

#define OP_EXIT             (INSTRUCAO)0b11111111

char *optoa(INSTRUCAO op);
PALAVRA convert_i64_i40(int64_t pal);
int64_t convert_i40_i64(PALAVRA pal);

#endif