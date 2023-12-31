#ifndef __DETAILS_HV_MAP_MEM_H__
#define __DETAILS_HV_MAP_MEM_H__

#include "obj.h"
#include "mem.h"

extern obj_trait* map_mem_t;
typedef struct    map_mem  {
    obj         head;
    mem_res    *res ;
    void       *mem ;
    struct map *map ;
}   map_mem;

bool_t map_mem_new  (map_mem*, u32_t, va_list);
bool_t map_mem_clone(map_mem*, map_mem*)      ;
void   map_mem_del  (map_mem*)                ;

#endif