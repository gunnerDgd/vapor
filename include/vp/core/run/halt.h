#ifndef __VP_CORE_RUN_HALT_H__
#define __VP_CORE_RUN_HALT_H__

#include "../cpu.h"

extern  obj_trait *vp_halt_t;
typedef obj*       vp_halt  ;

vp_cpu vp_halt_cpu(vp_halt) ;

#endif