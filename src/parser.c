//===--------------------------------------------------------------------------------------------===
// parser.c - recursive descent parser for Compass Redux
//
// Created by Amy Parent <developer@amyparent.com>
// Copyright (c) 2020 Amy Parent
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#include "parser.h"
#include <ccore/log.h>
#include <ctype.h>
#include <stdio.h>

#define TOKEN_MK_INVALID ((token_t){.kind=TOKEN_INVALID})
#define TOKEN_MK_END ((token_t){.kind=TOKEN_END})

void parser_fail(parser_t *parser, parse_error_t error) {
    longjmp(parser->exc, error);
}

static unicode_scalar_t lexer_advance(parser_t *parser) {
    CCASSERT(parser);
    if(parser->current == parser->end) return '\0';

    size_t bytes_left = parser->end - parser->current;
    uint8_t bytes_read = 0;
    unicode_scalar_t uc = unicode_utf8_read(parser->current, bytes_left, &bytes_read);
    if(!bytes_read) return '\0';
    if(uc == '\n') parser->is_line_start = true;
    parser->current += bytes_read;
    return parser->current_char = uc;
}

static unicode_scalar_t lexer_peek(parser_t *parser) {
    size_t bytes_left = parser->end - parser->current;
    uint8_t bytes_read = 0;
    return unicode_utf8_read(parser->current, bytes_left, &bytes_read);
}

static unicode_scalar_t parser_peek_next(parser_t *parser) {
    size_t bytes_left = parser->end - parser->current;
    uint8_t scalar_size = 0;
    unicode_utf8_read(parser->current, bytes_left, &scalar_size);
    bytes_left -= scalar_size;
    return unicode_utf8_read(parser->current + scalar_size, bytes_left, &scalar_size);
}

static bool lexer_match(parser_t *parser, unicode_scalar_t c) {
    if(lexer_peek(parser) == c) {
        lexer_advance(parser);
        return true;
    }
    return false;
}

static inline token_t lex_invalid(parser_t *parser) {
    parser->current_token = (token_t){.kind=TOKEN_INVALID, .begin=parser->current, .size=0};
    parser->is_line_start = false;
    return parser->current_token;
}

static inline token_t lex_end(parser_t *parser) {
    parser->current_token = (token_t){.kind=TOKEN_END, .begin=parser->end, .size=0};
    parser->is_line_start = false;
    return parser->current_token;
}

static inline token_t lex(parser_t *parser, token_kind_t kind) {
    parser->current_token = (token_t){
        .kind = kind,
        .is_line_start = parser->is_line_start,
        .begin = parser->token_begin,
        .size = parser->current - parser->token_begin
    };
    parser->is_line_start = false;
    return parser->current_token;
}

static token_t lex_string(parser_t *parser, unicode_scalar_t delim) {
    //parser->token_begin = parser->current;
    while(lexer_peek(parser) != delim) {
        lexer_advance(parser);
    }
    lexer_advance(parser);
    lex(parser, TOKEN_STRING);
    return parser->current_token;
}

static inline bool is_word_head(unicode_scalar_t c) {
    return unicode_is_identifier_head(c);
}

static inline bool is_word_continuation(unicode_scalar_t c) {
    return unicode_is_identifier(c) || c == '-' || c == '_';
}

static token_t lex_word(parser_t *parser) {
    while(is_word_continuation(lexer_peek(parser))) {
        lexer_advance(parser);
    }
    lex(parser, TOKEN_WORD);
    parser->current_token.kind = compass_token_for_keyword(
            parser->current_token.begin,
            parser->current_token.size
    );
    return parser->current_token;
}

static token_t lex_number(parser_t *parser) {
    while(isdigit(lexer_peek(parser))) {
        lexer_advance(parser);
    }
    return lex(parser, TOKEN_INTEGER);
}

static token_t next(parser_t *parser) {
    CCASSERT(parser);
    
    if(parser->current_token.kind == TOKEN_END) return lex_end(parser);
    if(!parser->current_char) return lex_end(parser);

    while(lexer_peek(parser) && parser->current != parser->end) {

        parser->token_begin = parser->current;
        unicode_scalar_t c = lexer_advance(parser);

        switch(c) {
        case 0x0020:
        case 0x000d:
        case 0x0009:
        case 0x000b:
        case 0x000c:
        case 0x000a:
            continue;
        
        case '\'':
        case '"':
            return lex_string(parser, c);

        case '.': return lex(parser, TOKEN_PERIOD);
        case ',': return lex(parser, TOKEN_COMMA);
        case ':': return lex(parser, TOKEN_COLON);
        case '[': return lex(parser, TOKEN_LBRACKET);
        case ']': return lex(parser, TOKEN_RBRACKET);
        case '(': return lex(parser, TOKEN_LPAREN);
        case ')': return lex(parser, TOKEN_RPAREN);
        
        case '-':
        case '+':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':

            break;

        default:
            if(is_word_head(c)) return lex_word(parser);
            return lex_invalid(parser);
        }
    }
    return lex_invalid(parser);
}


void parser_init(parser_t *parser, const char *input, const char *end) {
    CCASSERT(parser);
    CCASSERT(input);
    CCASSERT(end);
    CCASSERT(input <= end);

    
    parser->begin = input;
    parser->end = end;
    parser->current = input;
    parser->token_begin = input;
    parser->is_line_start = true;
    
    //lexer_advance(parser);
}

int64_t compass_dump_tokens(const char *src, const char *end) {
    CCASSERT(src);
    CCASSERT(end);

    parser_t parser;
    parser_init(&parser, src, end);

    token_t tok = next(&parser);
    while(tok.kind != TOKEN_END && tok.kind != TOKEN_INVALID) {
        printf("%-12s %-8s `%.*s`\n",
                tok.is_line_start ? "[line start]" : "",
                compass_token_get_name(tok.kind),
                tok.size,
                tok.begin);
        tok = next(&parser);
    }
}

