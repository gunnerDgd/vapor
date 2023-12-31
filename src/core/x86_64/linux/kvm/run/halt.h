#ifndef __CORE_KVM_RUN_HALT_H__
#define __CORE_KVM_RUN_HALT_H__

#include <obj.h>

extern obj_trait *vp_halt_t;
typedef struct    vp_halt  {
    obj            head;
    struct vp_run* run ;
    struct vp_cpu* cpu ;
}   vp_halt;

bool_t         vp_halt_new  (vp_halt*, u32_t, va_list);
bool_t         vp_halt_clone(vp_halt*, vp_halt*)      ;
void           vp_halt_del  (vp_halt*)                ;
struct vp_cpu* vp_halt_cpu  (vp_halt*)                ;

#endif