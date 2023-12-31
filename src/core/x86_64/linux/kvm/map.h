#ifndef __CORE_KVM_MAP_H__
#define __CORE_KVM_MAP_H__

#include <obj.h>
#include <map.h>

#include <linux/kvm.h>
#include <linux/kvm_para.h>

typedef struct vp_map_ops                      {
        struct vp_mmio_ops *ops_mmio; obj* mmio;
        struct vp_pio_ops  *ops_pio ; obj* pio ;
        void               *mem     ;
}       vp_map_ops;

extern obj_trait *vp_map_t                       ;
typedef struct    vp_map                         {
    obj                                head      ;
    u64_t                              begin, end;
    u64_t                              size      ;
    map                                sub       ;
    map_elem                           sup_hnd   ;
    struct vp_map                     *sup       ;
    struct vp_mmu                     *mmu       ;
    struct kvm_userspace_memory_region map       ;
    vp_map_ops                         ops       ;
}   vp_map;

bool_t  vp_map_new     (vp_map*, u32_t, va_list);
bool_t  vp_map_clone   (vp_map*, vp_map*)       ;
bool_t  vp_map_del     (vp_map*)                ;

vp_map* vp_map_sup     (vp_map*)                ;
vp_map* vp_map_sub     (vp_map*, vp_map*)       ;
vp_map* vp_map_sub_next(vp_map*, vp_map*)       ;
vp_map* vp_map_find    (vp_map*, u64_t, u64_t)  ;

u64_t   vp_map_begin   (vp_map*);
u64_t   vp_map_end     (vp_map*);
u64_t   vp_map_size    (vp_map*);

bool_t  vp_map_free    (vp_map*)                ;
bool_t  vp_map_sect    (vp_map*)                ;
bool_t  vp_map_mmio    (vp_map*)                ;
bool_t  vp_map_pio     (vp_map*)                ;
bool_t  vp_map_mem     (vp_map*)                ;


#endif