#ifndef __CORE_KVM_TASK_H__
#define __CORE_KVM_TASK_H__

#include <obj.h>

#define           vp_run_mmio 0
#define           vp_run_pio  1
#define           vp_run_halt 2
extern obj_trait *vp_run_t;
typedef struct    vp_run  {
    obj            head;
    struct vp_sys *sys ;
    struct vp_cpu *cpu ;
    struct vp_mmu *mmu ;
    obj           *run ;
}   vp_run;

bool_t vp_run_new  (vp_run*, u32_t, va_list);
bool_t vp_run_clone(vp_run*, vp_run*)       ;
void   vp_run_del  (vp_run*)                ;

u64_t  vp_run_type (vp_run*);

#endif