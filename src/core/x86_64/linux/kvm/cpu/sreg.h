#ifndef __CORE_KVM_CPU_SEG_H__
#define __CORE_KVM_CPU_SEG_H__

#include "../cpu.h"

#include <linux/kvm.h>
#include <linux/kvm_para.h>

#define vp_cs  0
#define vp_ds  1
#define vp_es  2
#define vp_fs  3
#define vp_ss  4
#define vp_tr  5
#define vp_ldt 6

#define vp_gdt 0
#define vp_idt 1

extern obj_trait *vp_sreg_t ;
typedef struct    vp_sreg   {
    obj                 head;
    vp_cpu             *cpu ;
    struct kvm_sregs    sreg;
    struct kvm_segment *seg ;
    struct kvm_dtable  *desc;
}   vp_sreg;

bool_t vp_sreg_new    (vp_sreg*, u32_t, va_list);
bool_t vp_sreg_clone  (vp_sreg*, vp_sreg*)      ;
void   vp_sreg_del    (vp_sreg*)                ;

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