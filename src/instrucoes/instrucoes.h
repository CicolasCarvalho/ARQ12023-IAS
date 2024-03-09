#ifndef INSTRUCOES_H_
#define INSTRUCOES_H_

#include "../utils.h"
#include "../pipeline/pipeline.h"

#include "OP_LSH.h"
#include "OP_RSH.h"
#include "OP_LOAD.h"
#include "OP_STOR.h"
#include "OP_LOAD_MENOS.h"
#include "OP_LOAD_MOD.h"
#include "OP_LOAD_MENOS_MOD.h"
#include "OP_LOAD_MQ.h"
#include "OP_LOAD_MQ_M.h"
#include "OP_JUMP_L.h"
#include "OP_JUMP_R.h"
#include "OP_JUMP_COND_L.h"
#include "OP_JUMP_COND_R.h"
#include "OP_ADD.h"
#include "OP_ADD_MOD.h"
#include "OP_SUB.h"
#include "OP_SUB_MOD.h"
#include "OP_MUL.h"
#include "OP_DIV.h"
#include "OP_STOR_L.h"
#include "OP_STOR_R.h"
#include "OP_EXIT.h"

void add_instrucoes(Pipeline *pipeline);

#endif
