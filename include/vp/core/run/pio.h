#ifndef __CORE_RUN_PIO_H__
#define __CORE_RUN_PIO_H__

#include <obj.h>

extern  obj_trait *vp_pio_t;
typedef obj       *vp_pio  ;

u64_t vp_pio_addr (vp_pio);
u64_t vp_pio_dir  (vp_pio);
u64_t vp_pio_size (vp_pio);

#endif