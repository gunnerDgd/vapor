#ifndef __CORE_KVM_RUN_MMIO_H__
#define __CORE_KVM_RUN_MMIO_H__

#include <obj.h>

#define           vp_mmio_in  0
#define           vp_mmio_out 1
extern obj_trait* vp_mmio_t;
typedef struct    vp_mmio  {
    obj            head;
    struct vp_run *run ;
    u64_t          dir ;
    u64_t          addr;
    u64_t          size;
    void          *data;
}   vp_mmio;

bool_t vp_mmio_new  (vp_mmio*, u32_t, va_list);
bool_t vp_mmio_clone(vp_mmio*, vp_mmio*)      ;
void   vp_mmio_del  (vp_mmio*)                ;

u64_t  vp_mmio_dir  (vp_mmio*);
u64_t  vp_mmio_addr (vp_mmio*);
u64_t  vp_mmio_size (vp_mmio*);

#endif