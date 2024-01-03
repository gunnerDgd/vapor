#ifndef __CORE_KVM_MAP_H__
#define __CORE_KVM_MAP_H__

#include <obj.h>
#include <map.h>

#include <linux/kvm.h>
#include <linux/kvm_para.h>

typedef struct vp_map_ops   {
    struct vp_mmio_ops *mmio;
    struct vp_pio_ops  *pio ;
}   vp_map_ops;

extern obj_trait *vp_map_t                       ;
typedef struct    vp_map                         {
    obj                                head      ;
    u64_t                              begin, end;
    u64_t                              size      ;
    struct vp_mmu                     *mmu       ;
    map_elem                           mmu_hnd   ;
    struct kvm_userspace_memory_region mem       ;
    vp_map_ops                         map_ops   ;
    obj*                               map       ;
}   vp_map;

bool_t  vp_map_new     (vp_map*, u32_t, va_list);
bool_t  vp_map_clone   (vp_map*, vp_map*)       ;
bool_t  vp_map_del     (vp_map*)                ;

u64_t   vp_map_begin   (vp_map*)                ;
u64_t   vp_map_end     (vp_map*)                ;
u64_t   vp_map_size    (vp_map*)                ;

bool_t  vp_map_none    (vp_map*)                ;
bool_t  vp_map_mmio    (vp_map*)                ;
bool_t  vp_map_pio     (vp_map*)                ;
bool_t  vp_map_mem     (vp_map*)                ;


#endif