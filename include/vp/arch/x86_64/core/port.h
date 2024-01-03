#ifndef __ARCH_X86_64_CORE_PORT_H__
#define __ARCH_X86_64_CORE_PORT_H__

#include "../../../core/map.h"
#include "../../../core/root.h"

vp_map  vp_map_pio  (vp_map, vp_map_ops*, obj*);

vp_map  vp_port_map (vp_root, u64_t, u64_t)    ;
vp_map  vp_port_find(vp_root, u64_t, u64_t)    ;

#endif