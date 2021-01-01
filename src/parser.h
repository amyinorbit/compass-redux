//===--------------------------------------------------------------------------------------------===
// parser.h - lexing and parsing interface for Compass Redux
//
// Created by Amy Parent <developer@amyparent.com>
// Copyright (c) 2020 Amy Parent
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <unic/unic.h>
#include <stddef.h>
#include <setjmp.h>
#include <compass/tokens.h>

typedef enum {
    PARSE_OK,
    PARSE_INVALID_TOKEN,
    PARSE_UNEXPECTED,
} parse_error_t;

typedef struct {
    const char *begin;
    const char *end;
    const char *token_begin;
    const char *current;
    
    bool is_line_start;

    jmp_buf exc;
    token_t current_token;
    unicode_scalar_t current_char;
} parser_t;


void parser_init(parser_t *parser, const char *input, const char *end);

bool parser_next_token(parser_t *parser);




