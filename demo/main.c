//===--------------------------------------------------------------------------------------------===
// main.c - Running demo/test file for compass development.
//
// Created by Amy Parent <developer@amyparent.com>
// Copyright (c) 2020 Amy Parent
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#include <compass/compiler.h>
#include <string.h>
#include <stdio.h>

static const char *test_story = "the kitchen is a location: 'Hello there!'.";

int main(int argc, const char **argv) {
    
    compass_dump_tokens(test_story, test_story + strlen(test_story));

}

