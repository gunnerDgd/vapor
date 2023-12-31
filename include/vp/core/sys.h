#ifndef __VP_CORE_SYS_H__
#define __VP_CORE_SYS_H__

#include "cpu.h"
#include "mmu.h"

extern  obj_trait* vp_sys_t;
typedef obj*       vp_sys  ;

vp_cpu vp_sys_cpu(vp_sys, vp_cpu);
vp_mmu vp_sys_mmu(vp_sys)        ;

#endif