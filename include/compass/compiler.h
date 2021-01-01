//===--------------------------------------------------------------------------------------------===
// compiler.h - Public Compass compiler interface
//
// Created by Amy Parent <developer@amyparent.com>
// Copyright (c) 2020 Amy Parent
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int64_t compass_dump_tokens(const char *src, const char *end);

#ifdef __cplusplus
} /* extern "C" */
#endif

