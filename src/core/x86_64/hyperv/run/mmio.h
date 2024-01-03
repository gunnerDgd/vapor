#ifndef __CORE_KVM_RUN_MMIO_H__
#define __CORE_KVM_RUN_MMIO_H__

#include "../details/run/mmio.h"

u64_t vp_mmio_dir (vp_mmio*);
u64_t vp_mmio_addr(vp_mmio*);
u64_t vp_mmio_size(vp_mmio*);

#endif