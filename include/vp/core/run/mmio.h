#ifndef __VP_CORE_RUN_MMIO_H__
#define __VP_CORE_RUN_MMIO_H__

#include <obj.h>

#define             vp_mmio_in  0
#define             vp_mmio_out 1
extern  obj_trait  *vp_mmio_t;
typedef obj*        vp_mmio  ;

u64_t  vp_mmio_dir (vp_mmio);
u64_t  vp_mmio_addr(vp_mmio);
u64_t  vp_mmio_size(vp_mmio);

#endif