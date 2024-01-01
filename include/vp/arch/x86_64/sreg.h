#ifndef __VP_ARCH_X86_64_SREG_H__
#define __VP_ARCH_X86_64_SREG_H__

#ifdef PRESET_ARCH_X86_64
#include <obj.h>

#define vp_cs  0
#define vp_ds  1
#define vp_es  2
#define vp_fs  3
#define vp_ss  4
#define vp_tr  5
#define vp_ldt 6

#define vp_gdt 0
#define vp_idt 1

extern  obj_trait *vp_sreg_t;
typedef obj       *vp_sreg  ;

u64_t  vp_desc_base   (vp_sreg, u64_t, u64_t*) ;
u64_t  vp_desc_limit  (vp_sreg, u64_t, u64_t*) ;

u64_t  vp_seg_base    (vp_sreg, u64_t, u64_t*);
u64_t  vp_seg_limit   (vp_sreg, u64_t, u64_t*);
u64_t  vp_seg_selector(vp_sreg, u64_t, u64_t*);
u64_t  vp_seg_type    (vp_sreg, u64_t, u64_t*);
u64_t  vp_seg_present (vp_sreg, u64_t, u64_t*);
u64_t  vp_seg_priv    (vp_sreg, u64_t, u64_t*);
u64_t  vp_seg_size    (vp_sreg, u64_t, u64_t*);
u64_t  vp_seg_desc    (vp_sreg, u64_t, u64_t*);
u64_t  vp_seg_long    (vp_sreg, u64_t, u64_t*);
u64_t  vp_seg_gran    (vp_sreg, u64_t, u64_t*);
u64_t  vp_seg_avail   (vp_sreg, u64_t, u64_t*);

#endif
#endif