#ifndef __VP_CORE_MMU_H__
#define __VP_CORE_MMU_H__

#include <obj.h>
#include "map.h"

typedef obj*            vp_mmu               ;
vp_map vp_mmu_map      (vp_mmu, vp_map)      ;
vp_map vp_mmu_find     (vp_mmu, u64_t, u64_t);
vp_map vp_mmu_find_port(vp_mmu, u64_t, u64_t);

#endif