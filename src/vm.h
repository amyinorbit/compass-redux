//===--------------------------------------------------------------------------------------------===
// vm.h - Compass virtual machine's internals
//
// Created by Amy Parent <developer@amyparent.com>
// Copyright (c) 2020 Amy Parent
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once
#include <compass/runtime.h>
#include <compass/value.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct memory_heap_t memory_heap_t;

struct compass_vm_t {
    memory_heap_t *heap;
    compass_value_t *stack;

    size_t code_size;
    uint32_t *code;
};

compass_value_t compass_obj_new(compass_vm_t *vm);




#ifdef __cplusplus
} /* extern "C" */
#endif

