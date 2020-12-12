//===--------------------------------------------------------------------------------------------===
// memory.h - Custom memory management system
//
// Created by Amy Parent <developer@amyparent.com>
// Copyright (c) 2020 Amy Parent
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct memory_heap_t memory_heap_t;

void memory_heap_init(void *region, size_t budget);

void *memory_alloc(void *region);

void memory_dealloc(void *region, void *obj);


#ifdef __cplusplus
} /* extern "C" */
#endif

