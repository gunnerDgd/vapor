#ifndef __CORE_KVM_CPU_H__
#define __CORE_KVM_CPU_H__

#include <obj.h>
#include <list.h>

#include <linux/kvm.h>
#include <linux/kvm_para.h>

#define           vp_cpu_off 0
#define           vp_cpu_on  1
#define           vp_cpu_run 2
extern obj_trait* vp_cpu_t  ;
typedef struct    vp_cpu    {
    obj             head    ;
    struct vp_sys*  sys     ;
    list_elem       sys_hnd ;
    u64_t           cpu     ;
    u64_t           cpu_id  ;
    u64_t           state   ;
    u64_t           run_size;
    struct kvm_run *run     ;
}   vp_cpu;

bool_t vp_cpu_new  (vp_cpu*, u32_t, va_list);
bool_t vp_cpu_clone(vp_cpu*, vp_cpu*)       ;
void   vp_cpu_del  (vp_cpu*)                ;

#endif