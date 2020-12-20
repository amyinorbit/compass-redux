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


/// Because that can get tricky with a language parser, we don't encode specific meaning of words
/// in lexed tokens. This is done through semantic analysis later on.
typedef enum {
   TOKEN_WORD,
   TOKEN_STRING,
   TOKEN_COMMA,
   TOKEN_PERIOD,
   TOKEN_LBRACKET,
   TOKEN_RBRACKET,
   TOKEN_LPAREN,
   TOKEN_RPAREN,
   TOKEN_COLON,
   TOKEN_INTEGER,
} token_kind_t;

typedef struct {
    const char *begin;
    uint32_t size;
    token_kind_t kind;
} token_t;

typedef struct {
    const char *begin;
    const char *end;
    const char *current;
    
    
    
    
#ifdef DEBUG_PARSE_STACK
    
#endif
} parser_t;

