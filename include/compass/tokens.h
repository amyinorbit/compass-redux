//===--------------------------------------------------------------------------------------------===
// tokens.h - Compass Redux tokens and inspection functions
//
// Created by Amy Parent <developer@amyparent.com>
// Copyright (c) 2020 Amy Parent
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    TOKEN_WORD,
    TOKEN_KW_IS,
    TOKEN_KW_HAS,
    TOKEN_KW_THING,
    TOKEN_KW_PLACE,
    TOKEN_KW_EXIT,
    TOKEN_KW_VERB,
    TOKEN_KW_WHEN,
    TOKEN_KW_CHECK,
    TOKEN_KW_ELSE,
    TOKEN_KW_END,
    TOKEN_STRING,
    TOKEN_COMMA,
    TOKEN_PERIOD,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_COLON,
    TOKEN_INTEGER,
    TOKEN_END,
    TOKEN_INVALID,
} token_kind_t;

typedef struct {
    const char *begin;
    uint32_t size;
    token_kind_t kind;
    bool is_line_start;
} token_t;

const char *compass_token_get_name(token_kind_t kind);
token_kind_t compass_token_for_keyword(const char *word, size_t size);

#ifdef __cplusplus
} /* extern "C" */
#endif

