#ifndef __CORE_HYPERV_DETAILS_CPU_H__
#define __CORE_HYPERV_DETAILS_CPU_H__

#include <obj.h>
#include <list.h>

#include "core.h"

#define           vp_cpu_off  0
#define           vp_cpu_on   1
#define           vp_cpu_exit 2
extern obj_trait* vp_cpu_t          ;
typedef struct    vp_cpu            {
    obj                     head    ;
    struct vp_root*         root    ;
    struct vp_node*         node    ;
    u64_t                   cpu     ;
    u64_t                   state   ;
    WHV_EMULATOR_HANDLE     emu     ;
    obj                    *run_task;
    WHV_RUN_VP_EXIT_CONTEXT run     ;
}   vp_cpu;

bool_t vp_cpu_new  (vp_cpu*, u32_t, va_list);
bool_t vp_cpu_clone(vp_cpu*, vp_cpu*)       ;
void   vp_cpu_del  (vp_cpu*)                ;

#endif