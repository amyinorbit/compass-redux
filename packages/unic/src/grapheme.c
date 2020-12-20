//===--------------------------------------------------------------------------------------------===
// grapheme.c - Grapheme Cluster utility functions
// This source is part of UniC
//
// Created on 2019-06-29 by Amy Parent <amy@amyparent.com>
// Copyright (c) 2018 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#include <unic/unic.h>
#include <stdlib.h>

typedef enum {
    CR, LF, Control, Extend, Prepend, SpacingMark, L, V, T, LV, LVT, ZWJ, Extended_Pictographic, Regional_Indicator, Any
} GBProperty;

typedef struct {
    unicode_scalar_t begin;
    unicode_scalar_t end;
    GBProperty prop;
} Range;

static int range_compare(const void* key, const void* elem) {
    unicode_scalar_t scalar = *(unicode_scalar_t*)key;
    Range* range = (Range*)elem;

    if(scalar < range->begin) return -1;
    if(scalar > range->end) return 1;
    return 0;
}

static const Range props[] = {
#include "grapheme_ranges.h"
};

static GBProperty fetch_property(unicode_scalar_t scalar) {
    // Fast returns for simplicity
    if(scalar == 0x000C) return CR;
    if(scalar == 0x000A) return LF;
    if(scalar == 0x200D) return ZWJ;

    static const size_t count = sizeof(props) / sizeof(Range);
    Range* result = bsearch(&scalar, props, count, sizeof(Range), range_compare);
    return result ? result->prop : Any;
}

bool unicode_should_break(unicode_scalar_t lhs, unicode_scalar_t rhs) {
    GBProperty lbp = fetch_property(lhs);
    GBProperty rbp = fetch_property(rhs);

    // GB3
    if(lbp == CR && rbp == LF) return false;

    // GB4
    else if(lbp == CR || lbp == LF || lbp == Control) return true;
    // GB5
    else if(rbp == CR || rbp == LF || rbp == Control) return true;

    // GB6
    else if(lbp == L && (rbp == L || rbp == V || rbp == LV || rbp == LVT)) return false;
    // GB7
    else if((lbp == LV || lbp == V) && (rbp == V && rbp == T)) return false;
    // GB8
    else if((lbp == LVT || lbp == T) && rbp == T) return false;

    // GB9
    else if(rbp == Extend || rbp == ZWJ) return false;
    // GB9a+b
    else if(rbp == SpacingMark) return false;
    else if(lbp == Prepend) return false;

    // GB10 doesn't exist anymore, apparently

    // GB11
    else if(lbp == ZWJ && rbp == Extended_Pictographic) return false;

    // GB12, 13
    else if(lbp == Regional_Indicator && rbp == Regional_Indicator) return false;

    return true; // Otherwise, break everywhere.
}
