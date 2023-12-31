#ifndef __DETAILS_HV_RUN_H__
#define __DETAILS_HV_RUN_H__

#include "obj.h"

#include <WinHvPlatform.h>
#include <WinHvPlatformDefs.h>

#define run_mmio WHvRunVpExitReasonMemoryAccess
#define run_port WHvRunVpExitReasonX64IoPortAccess
#define run_expt WHvRunVpExitReasonUnrecoverableException
#define run_intr WHvRunVpExitReasonX64InterruptWindow
#define run_halt WHvRunVpExitReasonX64Halt
#define run_eoi  WHvRunVpExitReasonX64ApicEoi

extern obj_trait* run_t         ;
typedef struct    run           {
    obj                     head;
    WHV_RUN_VP_EXIT_CONTEXT task;
    struct vcpu            *vcpu;
}   run;

bool_t run_new  (run*, u32_t, va_list);
bool_t run_clone(run*, run*)          ;
bool_t run_del  (run*)                ;

#endif