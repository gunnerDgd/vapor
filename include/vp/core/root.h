#ifndef __CORE_ROOT_H__
#define __CORE_ROOT_H__

#include "node.h"

extern  obj_trait *vp_root_t;
typedef obj       *vp_root  ;

vp_node vp_root_node     (vp_root, vp_node)     ;
vp_map  vp_root_map      (vp_root, u64_t, u64_t);
vp_map  vp_root_map_find (vp_root, u64_t, u64_t);

#endif