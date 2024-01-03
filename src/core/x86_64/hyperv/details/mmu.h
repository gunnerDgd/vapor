#ifndef __CORE_HYPERV_DETAILS_MMU_H__
#define __CORE_HYPERV_DETAILS_MMU_H__

#include <obj.h>
#include <map.h>

#include "map.h"

extern obj_trait* vp_mmu_t    ;
typedef struct    vp_mmu      {
    obj             head      ;
    struct vp_node *node      ;
    struct vp_root *root      ;
    u64_t           begin, end;
    map             mmu       ;
}   vp_mmu;

bool_t vp_mmu_new  (vp_mmu*, u32_t, va_list);
bool_t vp_mmu_clone(vp_mmu*, vp_mmu*)       ;
void   vp_mmu_del  (vp_mmu*)                ;

void*  vp_mmu_map  (vp_mmu*, vp_map*)       ;
void*  vp_mmu_find (vp_mmu*, u64_t, u64_t)  ;

#endif