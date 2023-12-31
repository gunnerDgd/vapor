#ifndef __VP_CORE_RUN_PIO_H__
#define __VP_CORE_RUN_PIO_H__

#include <obj.h>

#define             vp_pio_in  0
#define             vp_pio_out 1
extern  obj_trait  *vp_pio_t;
typedef obj*        vp_pio  ;

u64_t  vp_pio_addr (vp_pio*);
u64_t  vp_pio_dir  (vp_pio*);
u64_t  vp_pio_size (vp_pio*);

#endif