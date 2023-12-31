#ifndef __VP_CORE_MAP_H__
#define __VP_CORE_MAP_H__

#include <obj.h>

extern  obj_trait* vp_map_t;
typedef obj*       vp_map  ;

vp_map vp_map_sup     (vp_map)              ;
vp_map vp_map_sub     (vp_map, vp_map)      ;
vp_map vp_map_sub_next(vp_map, vp_map)      ;
vp_map vp_map_find    (vp_map, u64_t, u64_t);

u64_t  vp_map_begin   (vp_map)              ;
u64_t  vp_map_end     (vp_map)              ;
u64_t  vp_map_size    (vp_map)              ;

bool_t vp_map_free    (vp_map)              ;
bool_t vp_map_sect    (vp_map)              ;
bool_t vp_map_mmio    (vp_map)              ;
bool_t vp_map_pio     (vp_map)              ;
bool_t vp_map_mem     (vp_map)              ;

#endif