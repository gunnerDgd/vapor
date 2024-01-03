#ifndef __CORE_KVM_DETAILS_RUN_MMIO_H__
#define __CORE_KVM_DETAILS_RUN_MMIO_H__

#include <obj.h>

#define           vp_mmio_in  0
#define           vp_mmio_out 1
extern obj_trait* vp_mmio_t;
typedef struct    vp_mmio  {
    obj             head;
    struct vp_cpu  *cpu ;
    struct vp_node *node;
    struct vp_root *root;

    u64_t           dir ;
    u64_t           addr;
    u64_t           size;
    void*           data;
}   vp_mmio;

bool_t vp_mmio_new  (vp_mmio*, u32_t, va_list);
bool_t vp_mmio_clone(vp_mmio*, vp_mmio*)      ;
void   vp_mmio_del  (vp_mmio*)                ;

#endif