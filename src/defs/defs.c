#include "defs.h"

char *optoa(INSTRUCAO op) {
    switch (op)
    {
        case (INSTRUCAO)0b00010100:
            return "OP_LSH";
        case (INSTRUCAO)0b00010101:
            return "OP_RSH";
        case (INSTRUCAO)0b00000001:
            return "OP_LOAD";
        case (INSTRUCAO)0b00100001:
            return "OP_STOR";
        case (INSTRUCAO)0b00000010:
            return "OP_LOAD_MENOS";
        case (INSTRUCAO)0b00000011:
            return "OP_LOAD_MOD";
        case (INSTRUCAO)0b00000100:
            return "OP_LOAD_MENOS_MOD";
        case (INSTRUCAO)0b00001010:
            return "OP_LOAD_MQ";
        case (INSTRUCAO)0b00001001:
            return "OP_LOAD_MQ_M";
        case (INSTRUCAO)0b00001101:
            return "OP_JUMP_L";
        case (INSTRUCAO)0b00001110:
            return "OP_JUMP_R";
        case (INSTRUCAO)0b00001111:
            return "OP_JUMP_COND_L";
        case (INSTRUCAO)0b00010000:
            return "OP_JUMP_COND_R";
        case (INSTRUCAO)0b00000101:
            return "OP_ADD";
        case (INSTRUCAO)0b00000111:
            return "OP_ADD_MOD";
        case (INSTRUCAO)0b00000110:
            return "OP_SUB";
        case (INSTRUCAO)0b00001000:
            return "OP_SUB_MOD";
        case (INSTRUCAO)0b00001011:
            return "OP_MUL";
        case (INSTRUCAO)0b00001100:
            return "OP_DIV";
        case (INSTRUCAO)0b00010010:
            return "OP_STOR_L";
        case (INSTRUCAO)0b00010011:
            return "OP_STOR_R";
        case (INSTRUCAO)0b11111111:
            return "OP_EXIT";       
    default:
        return "unknown";
    }
}