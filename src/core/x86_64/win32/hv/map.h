#ifndef __DETAILS_HV_MAP_H__
#define __DETAILS_HV_MAP_H__

#include "obj.h"
#include "list.h"

extern obj_trait* map_t   ;
typedef struct    map     {
    obj         head      ;
    u64_t       begin, end;
    u64_t       size      ;
    list        sub       ;
    list_elem   sup_hnd   ;
    struct map *sup       ;
    struct mmu *mmu       ;
    obj        *map       ;
}   map;

bool_t map_new     (map*, u32_t, va_list);
bool_t map_clone   (map*, map*)          ;
bool_t map_del     (map*)                ;

map*   map_sup     (map*)                ;
map*   map_sub     (map*, map*)          ;
map*   map_sub_next(map*, map*)          ;
map*   map_find    (map*, u64_t, u64_t)  ;

#endif