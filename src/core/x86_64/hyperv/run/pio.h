#ifndef __CORE_KVM_RUN_PIO_H__
#define __CORE_KVM_RUN_PIO_H__

#include "../details/run/pio.h"

u64_t vp_pio_addr (vp_pio*);
u64_t vp_pio_dir  (vp_pio*);
u64_t vp_pio_size (vp_pio*);

#endif