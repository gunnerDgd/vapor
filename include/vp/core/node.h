#ifndef __CORE_NODE_H__
#define __CORE_NODE_H__

#include "cpu.h"
#include "map.h"

typedef void* vp_node;

vp_map vp_node_map     (vp_node, u64_t, u64_t);
vp_map vp_node_map_find(vp_node, u64_t, u64_t);
vp_map vp_node_map_next(vp_node, void*)       ;
vp_cpu vp_node_cpu     (vp_node, vp_cpu)      ;

#endif