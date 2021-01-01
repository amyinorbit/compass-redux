//===--------------------------------------------------------------------------------------------===
// tokens.c - Token inspection functions
//
// Created by Amy Parent <developer@amyparent.com>
// Copyright (c) 2020 Amy Parent
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#include <compass/tokens.h>
#include <ccore/log.h>
#include <string.h>

static const char *token_names[] = {
    [TOKEN_WORD]        = "word",
    [TOKEN_KW_IS]       = "kw_is",
    [TOKEN_KW_HAS]      = "kw_has",
    [TOKEN_KW_THING]    = "kw_thing",
    [TOKEN_KW_PLACE]    = "kw_place",
    [TOKEN_KW_EXIT]     = "kw_exit",
    [TOKEN_KW_VERB]     = "kw_verb",
    [TOKEN_KW_WHEN]     = "kw_when",
    [TOKEN_KW_CHECK]    = "kw_check",
    [TOKEN_KW_ELSE]     = "kw_else",
    [TOKEN_KW_END]      = "kw_end",
    [TOKEN_STRING]      = "string",
    [TOKEN_COMMA]       = "comma",
    [TOKEN_PERIOD]      = "period",
    [TOKEN_LBRACKET]    = "l_bracket",
    [TOKEN_RBRACKET]    = "r_bracket",
    [TOKEN_LPAREN]      = "l_paren",
    [TOKEN_RPAREN]      = "r_paren",
    [TOKEN_COLON]       = "colon",
    [TOKEN_INTEGER]     = "integer",
    [TOKEN_END]         = "end",
    [TOKEN_INVALID]     = "invalid",
};

const char *compass_token_get_name(token_kind_t kind) {
    CCASSERT(kind >= TOKEN_WORD && kind <= TOKEN_INVALID);
    return token_names[kind];
}

token_kind_t compass_token_for_keyword(const char *begin, size_t size) {

    static const struct {
        const char *word;
        token_kind_t kind;
        size_t size;
    } table[] = {
        {"is",      TOKEN_KW_IS,    2},
        {"are",     TOKEN_KW_IS,    3},
        {"has",     TOKEN_KW_HAS,   3},
        {"have",    TOKEN_KW_HAS,   4},

        {"thing",   TOKEN_KW_THING, 5},
        {"things",  TOKEN_KW_THING, 6},
        {"place",   TOKEN_KW_PLACE, 5},
        {"exit",    TOKEN_KW_EXIT,  4},
        {"exits",   TOKEN_KW_EXIT,  5},
        {"verb",    TOKEN_KW_VERB,  4},
        {"when",    TOKEN_KW_WHEN,  4},
        {"check",   TOKEN_KW_CHECK, 5},
        {"else",    TOKEN_KW_ELSE,  4},
        {"end",     TOKEN_KW_END,   3},
        {NULL,      TOKEN_INVALID},
    };
    for(int i = 0; table[i].word; ++i) {
        if(table[i].size == size && !strncmp(table[i].word, begin, size)) return table[i].kind;
    }
    return TOKEN_WORD;
}

