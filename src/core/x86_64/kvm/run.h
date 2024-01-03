#ifndef __CORE_KVM_TASK_H__
#define __CORE_KVM_TASK_H__

#include <obj.h>

#include "cpu.h"
#include "sys.h"
#include "mmu.h"

#define           vp_run_mmio 0
#define           vp_run_pio  1
#define           vp_run_halt 2
extern obj_trait *vp_run_t  ;
typedef struct    vp_run    {
    obj             head    ;
    struct vp_cpu  *cpu     ;
    obj            *run_task;
    struct kvm_run *run     ;
}   vp_run;

bool_t  vp_run_new  (vp_run*, u32_t, va_list);
bool_t  vp_run_clone(vp_run*, vp_run*)       ;
void    vp_run_del  (vp_run*)                ;

u64_t   vp_run_type (vp_run*)                ;
vp_cpu* vp_run_cpu  (vp_run*)                ;
vp_sys* vp_run_sys  (vp_run*)                ;
vp_mmu* vp_run_mmu  (vp_run*)                ;

#endif