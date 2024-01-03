#ifndef __CORE_HYPERV_DETAILS_MAP_H__
#define __CORE_HYPERV_DETAILS_MAP_H__

#include <obj.h>
#include <map.h>

typedef struct vp_map_ops                     {
    bool_t (*read) (obj*, void*, void*, u64_t);
    bool_t (*write)(obj*, void*, void*, u64_t);
    bool_t (*map)  (obj*, void*)              ;
    bool_t (*unmap)(obj*)                     ;
}   vp_map_ops;

#define           vp_map_type_none 0
#define           vp_map_type_mmio 1
#define           vp_map_type_mem  2
#define           vp_map_type_pio  3
extern obj_trait *vp_map_t   ;
typedef struct    vp_map     {
    obj            head      ;
    u64_t          type      ;
    u64_t          begin, end;
    u64_t          size      ;
    struct vp_mmu *mmu       ;
    vp_map_ops    *map_ops   ;
    obj*           map       ;
}   vp_map;

bool_t vp_map_new  (vp_map*, u32_t, va_list);
bool_t vp_map_clone(vp_map*, vp_map*)       ;
void   vp_map_del  (vp_map*)                ;

#endif