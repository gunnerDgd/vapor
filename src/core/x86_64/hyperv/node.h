#ifndef __CORE_HYPERV_NODE_H__
#define __CORE_HYPERV_NODE_H__

#include "root.h"
#include "details/node.h"

void* vp_node_map     (void*, u64_t, u64_t);
void* vp_node_map_find(void*, u64_t, u64_t);
void* vp_node_map_next(void*, void*)       ;
void* vp_node_cpu     (void*, void*)       ;

#endif