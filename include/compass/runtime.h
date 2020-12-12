//===--------------------------------------------------------------------------------------------===
// runtime.h - Compass runtime redux
//
// Created by Amy Parent <amy@amyparent.com>
// Copyright (c) 2020 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct compass_vm_t compass_vm_t;

typedef enum {
    COMPASS_STYLE_NORMAL,
    COMPASS_STYLE_ITALICS,
} compass_style_t;

typedef struct {
    void (*set_style)(compass_style_t, void *);
    void (*write)(const char *, void *);
    size_t (*read)(char *, void *);
} compass_io_device_t;


compass_vm_t *compass_vm_new();

void compass_vm_delete(compass_vm_t *rt);

void compass_vm_run(compass_vm_t *rt, const char *begin, const char *end);

void compass_vm_add_io(compass_vm_t *rt, const compass_io_device_t *device, void *data);


#ifdef __cplusplus
} /* extern "C" */
#endif
