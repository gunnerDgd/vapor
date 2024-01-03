#ifndef __CORE_RUN_MMIO_H__
#define __CORE_RUN_MMIO_H__

#include <obj.h>

extern  obj_trait *vp_mmio_t;
typedef obj       *vp_mmio  ;

u64_t vp_mmio_dir (vp_mmio);
u64_t vp_mmio_addr(vp_mmio);
u64_t vp_mmio_size(vp_mmio);

#endif