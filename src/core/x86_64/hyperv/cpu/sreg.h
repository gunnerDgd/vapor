#ifndef __CORE_HYPERV_CPU_SREG_H__
#define __CORE_HYPERV_CPU_SREG_H__

#include "../details/cpu/sreg.h"

u64_t  vp_desc_base   (vp_sreg*, u64_t, u64_t*) ;
u64_t  vp_desc_limit  (vp_sreg*, u64_t, u64_t*) ;

u64_t  vp_seg_base    (vp_sreg*, u64_t, u64_t*);
u64_t  vp_seg_limit   (vp_sreg*, u64_t, u64_t*);
u64_t  vp_seg_selector(vp_sreg*, u64_t, u64_t*);
u64_t  vp_seg_type    (vp_sreg*, u64_t, u64_t*);
u64_t  vp_seg_present (vp_sreg*, u64_t, u64_t*);
u64_t  vp_seg_priv    (vp_sreg*, u64_t, u64_t*);
u64_t  vp_seg_size    (vp_sreg*, u64_t, u64_t*);
u64_t  vp_seg_desc    (vp_sreg*, u64_t, u64_t*);
u64_t  vp_seg_long    (vp_sreg*, u64_t, u64_t*);
u64_t  vp_seg_gran    (vp_sreg*, u64_t, u64_t*);
u64_t  vp_seg_avail   (vp_sreg*, u64_t, u64_t*);

#endif