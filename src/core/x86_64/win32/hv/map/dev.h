#ifndef __DETAILS_HV_MAP_DEV_H__
#define __DETAILS_HV_MAP_DEV_H__

#include "obj.h"
#include "list.h"

typedef struct map_dev_ops             {
    bool_t (*rd8)  (obj*, u8_t*)       ;
    bool_t (*rd16) (obj*, u16_t*)      ;
    bool_t (*rd32) (obj*, u32_t*)      ;
    bool_t (*rd64) (obj*, u64_t*)      ;
    bool_t (*read) (obj*, void*, u64_t);

    bool_t (*wr8)  (obj*, u8_t)        ;
    bool_t (*wr16) (obj*, u16_t)       ;
    bool_t (*wr32) (obj*, u32_t)       ;
    bool_t (*wr64) (obj*, u64_t)       ;
    bool_t (*write)(obj*, void*, u64_t);
}   map_dev_ops;

extern obj_trait* map_dev_t;
typedef struct    map_dev  {
    obj          head   ;
    struct map  *map    ;
    obj         *dev    ;
    map_dev_ops *dev_ops;
}   map_dev;

bool_t map_dev_new  (map_dev*, u32_t, va_list);
bool_t map_dev_clone(map_dev*, map_dev*)      ;
void   map_dev_del  (map_dev*)                ;

bool_t map_dev_rd8  (map_dev*, u8_t *)      ;
bool_t map_dev_rd16 (map_dev*, u16_t*)      ;
bool_t map_dev_rd32 (map_dev*, u32_t*)      ;
bool_t map_dev_rd64 (map_dev*, u64_t*)      ;
bool_t map_dev_read (map_dev*, void*, u64_t);

bool_t map_dev_wr8  (map_dev*, u8_t)        ;
bool_t map_dev_wr16 (map_dev*, u16_t)       ;
bool_t map_dev_wr32 (map_dev*, u32_t)       ;
bool_t map_dev_wr64 (map_dev*, u64_t)       ;
bool_t map_dev_write(map_dev*, void*, u64_t);

#endif