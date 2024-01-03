#ifndef __CORE_HYPERV_ROOT_H__
#define __CORE_HYPERV_ROOT_H__

#include "details/root.h"
#include "details/map.h"

void* vp_root_node     (vp_root*, void*)       ;
void* vp_root_map      (vp_root*, u64_t, u64_t);
void* vp_root_map_find (vp_root*, u64_t, u64_t);

void* vp_port_map      (vp_root*, u64_t, u64_t);
void* vp_port_find     (vp_root*, u64_t, u64_t);

#endif