#ifndef __CORE_HYPERV_MAP_H__
#define __CORE_HYPERV_MAP_H__

#include "details/map.h"

void*  vp_map_mmio (void*, vp_map_ops*, obj*);
void*  vp_map_pio  (void*, vp_map_ops*, obj*);
void*  vp_map_mem  (void*, void*)            ;

u64_t  vp_map_type (void*)                   ;
u64_t  vp_map_begin(void*)                   ;
u64_t  vp_map_end  (void*)                   ;
u64_t  vp_map_size (void*)                   ;

bool_t vp_map_read (void*, void*, void*, u64_t);
bool_t vp_map_write(void*, void*, void*, u64_t);


#endif