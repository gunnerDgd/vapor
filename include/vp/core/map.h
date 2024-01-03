#ifndef __CORE_MAP_H__
#define __CORE_MAP_H__

#include <obj.h>

typedef void*  vp_map;
typedef struct vp_map_ops                     {
    bool_t (*read) (obj*, void*, void*, u64_t);
    bool_t (*write)(obj*, void*, void*, u64_t);
    bool_t (*map)  (obj*, vp_map)             ;
    bool_t (*unmap)(obj*)                     ;
}   vp_map_ops;

vp_map  vp_map_mmio (vp_map, vp_map_ops*, obj*)  ;
vp_map  vp_map_mem  (vp_map, void*)              ;

u64_t   vp_map_type (vp_map)                     ;
u64_t   vp_map_begin(vp_map)                     ;
u64_t   vp_map_end  (vp_map)                     ;
u64_t   vp_map_size (vp_map)                     ;

bool_t  vp_map_read (vp_map, void*, void*, u64_t);
bool_t  vp_map_write(vp_map, void*, void*, u64_t);


#endif