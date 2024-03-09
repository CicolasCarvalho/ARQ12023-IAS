#include "instrucoes.h"

void add_instrucoes(Pipeline *pipeline) {
    ADD_OP_LSH(pipeline);
    ADD_OP_RSH(pipeline);
    ADD_OP_LOAD(pipeline);
    ADD_OP_STOR(pipeline);
    ADD_OP_LOAD_MENOS(pipeline);
    ADD_OP_LOAD_MOD(pipeline);
    ADD_OP_LOAD_MENOS_MOD(pipeline);
    ADD_OP_LOAD_MQ(pipeline);
    ADD_OP_LOAD_MQ_M(pipeline);
    ADD_OP_JUMP_L(pipeline);
    ADD_OP_JUMP_R(pipeline);
    ADD_OP_JUMP_COND_L(pipeline);
    ADD_OP_JUMP_COND_R(pipeline);
    ADD_OP_ADD(pipeline);
    ADD_OP_ADD_MOD(pipeline);
    ADD_OP_SUB(pipeline);
    ADD_OP_SUB_MOD(pipeline);
    ADD_OP_MUL(pipeline);
    ADD_OP_DIV(pipeline);
    ADD_OP_STOR_L(pipeline);
    ADD_OP_STOR_R(pipeline);
    ADD_OP_EXIT(pipeline);
}