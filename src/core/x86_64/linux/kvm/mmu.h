#ifndef __CORE_KVM_MMU_H__
#define __CORE_KVM_MMU_H__

#include <obj.h>
#include <list.h>

extern obj_trait* vp_mmu_t  ;
typedef struct    vp_mmu    {
    obj            head     ;
    struct vp_sys *sys      ;
    struct vp_map *map      ;
    u64_t          map_count;
}   vp_mmu;

bool_t         vp_mmu_new       (vp_mmu*, u32_t, va_list);
bool_t         vp_mmu_clone     (vp_mmu*, vp_mmu*)       ;
void           vp_mmu_del       (vp_mmu*)                ;

struct vp_map* vp_mmu_map       (vp_mmu*, struct vp_map*);
struct vp_map* vp_mmu_find      (vp_mmu*, u64_t)         ;
struct vp_map* vp_mmu_find_range(vp_mmu*, u64_t, u64_t)  ;

#endif