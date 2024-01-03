#ifndef __CORE_KVM_SYS_H__
#define __CORE_KVM_SYS_H__

#include <obj.h>
#include <list.h>

#include "cpu.h"
#include "mmu.h"

extern obj_trait *vp_sys_t;
typedef struct    vp_sys  {
    obj     head     ;
    u32_t   sys      ;
    list    cpu      ;
    u64_t   cpu_count;
    vp_cpu *bsp      ;
    vp_mmu *mmu      ;
    u64_t   state    ;
}   vp_sys;

bool_t  vp_sys_new  (vp_sys*, u32_t, va_list);
bool_t  vp_sys_clone(vp_sys*, vp_sys*)       ;
void    vp_sys_del  (vp_sys*)                ;

vp_cpu* vp_sys_cpu  (vp_sys*, vp_cpu*)       ;
vp_mmu* vp_sys_mmu  (vp_sys*)                ;
vp_cpu* vp_sys_bsp  (vp_sys*)                ;

#endif