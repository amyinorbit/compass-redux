//===--------------------------------------------------------------------------------------------===
// vm.c - implementation of most of Compass's redux VM
//
// Created by Amy Parent <developer@amyparent.com>
// Copyright (c) 2020 Amy Parent
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#include "vm.h"
#include "parser.h"

struct compass_vm_t {
    compass_ptr_t frame;
    compass_ptr_t locals;
    compass_ptr_t sp;
    compass_ptr_t rom;
    compass_ptr_t ram;
    compass_ptr_t entry;

    uint8_t *stack;
    uint8_t *heap;
};





