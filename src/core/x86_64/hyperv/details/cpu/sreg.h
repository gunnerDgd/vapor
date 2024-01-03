#ifndef __CORE_HYPERV_DETAILS_CPU_SREG_H__
#define __CORE_HYPERV_DETAILS_CPU_SREG_H__

#include "../core.h"

#define vp_cs  0
#define vp_ds  1
#define vp_es  2
#define vp_fs  3
#define vp_gs  4
#define vp_ss  5

#define vp_tr  6
#define vp_ldt 7

#define vp_gdt 8
#define vp_idt 9

extern obj_trait *vp_sreg_t     ;
typedef struct    vp_sreg       {
    obj                 head    ;
    struct vp_cpu      *cpu     ;
    struct vp_node     *node    ;
    struct vp_root     *root    ;
    WHV_REGISTER_VALUE  sreg[10];
}   vp_sreg;

bool_t vp_sreg_new    (vp_sreg*, u32_t, va_list);
bool_t vp_sreg_clone  (vp_sreg*, vp_sreg*)      ;
void   vp_sreg_del    (vp_sreg*)                ;

#endif