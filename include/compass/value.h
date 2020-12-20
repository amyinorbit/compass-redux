//===--------------------------------------------------------------------------------------------===
// value.h - Tagged value, main variable representation for StoryTime
//
// Created by Amy Parent <developer@amyparent.com>
// Copyright (c) 2020 Amy Parent
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct compass_obj_t compass_obj_t;
typedef struct compass_instance_t compass_instance_t;

typedef enum {
    COMPASS_VALUE_BOOL,
    COMPASS_VALUE_INT,
    COMPASS_VALUE_FLOAT,
    COMPASS_VALUE_STR,
    COMPASS_VALUE_TYPE,
    COMPASS_VALUE_OBJ,
} compass_value_kind_t;

typedef struct {
    compass_value_kind_t kind;
    union {
        float f32;
        int32_t i32;
        compass_obj_t *obj;
        uint32_t ref;
    };
} compass_value_t;

typedef struct {

} compass_field_t;

struct compass_instance_t {
    compass_obj_t *next;
    bool color;
};

struct compass_obj_t {
    compass_instance_t gc;
    uint16_t field_count;
    compass_value_t fields[];
};

struct compass_str_t {
    compass_instance_t gc;
    uint32_t size;
    uint32_t hash;
    char data[];
};

// No macros here, bitten once too many
static inline compass_value_t compass_true()
{ return (compass_value_t){.kind=COMPASS_VALUE_BOOL, .i32=1}; }
static inline compass_value_t compass_false()
{ return (compass_value_t){.kind=COMPASS_VALUE_BOOL, .i32=0}; }
static inline compass_value_t compass_int(int32_t v)
{ return (compass_value_t){.kind=COMPASS_VALUE_INT, .i32=v}; }
static inline compass_value_t compass_float(float v)
{ return (compass_value_t){.kind=COMPASS_VALUE_FLOAT, .f32=v}; }
static inline compass_value_t compass_obj(void *r)
{ return (compass_value_t){.kind=COMPASS_VALUE_OBJ, .obj=r}; }
static inline compass_value_t compass_str(uint32_t r)
{ return (compass_value_t){.kind=COMPASS_VALUE_STR, .ref=r}; }



#ifdef __cplusplus
} /* extern "C" */
#endif

