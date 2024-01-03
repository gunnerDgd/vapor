#ifndef __CORE_KVM_TASK_PIO_H__
#define __CORE_KVM_TASK_PIO_H__

#include <obj.h>

#define           vp_pio_in  0
#define           vp_pio_out 1
extern obj_trait *vp_pio_t;
typedef struct    vp_pio  {
    obj            head;
    struct vp_run *run ;
    u64_t          addr;
    u64_t          dir ;
    u64_t          size;
    void          *data;
}   vp_pio;

bool_t vp_pio_new  (vp_pio*, u32_t, va_list);
bool_t vp_pio_clone(vp_pio*, vp_pio*)       ;
void   vp_pio_del  (vp_pio*)                ;

u64_t  vp_pio_addr (vp_pio*);
u64_t  vp_pio_dir  (vp_pio*);
u64_t  vp_pio_size (vp_pio*);

#endif