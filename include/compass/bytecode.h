//===--------------------------------------------------------------------------------------------===
// bytecode.h - Bytecode debugging and printing. HERE BE DRAGONS (you probably do not need this)
//
// Created by Amy Parent <developer@amyparent.com>
// Copyright (c) 2020 Amy Parent
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define OPCODE(inst, bin, _, __) COMPASS_OP_##inst = bin,

/// Numerical value of one compass vm instruction.
typedef enum {
#include "inst.x.h"
} compass_opcode_t;
#undef OPCODE

extern const char *compass_opcode_str[COMPASS_OP_invalid];
extern const int compass_stack_effect[COMPASS_OP_invalid];
extern const int compass_operand_bytes[COMPASS_OP_invalid];

#ifdef __cplusplus
} /* extern "C" */
#endif

