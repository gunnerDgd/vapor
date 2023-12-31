#ifndef __VP_CORE_RUN_H__
#define __VP_CORE_RUN_H__

#include <obj.h>

#define            vp_run_mmio 0
#define            vp_run_pio  1
#define            vp_run_halt 2
extern  obj_trait *vp_run_t;
typedef obj*       vp_run  ;

u64_t vp_run_type (vp_run);

#endif