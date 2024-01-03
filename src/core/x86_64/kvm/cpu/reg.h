#ifndef __CORE_KVM_CPU_REG_H__
#define __CORE_KVM_CPU_REG_H__

#include "../cpu.h"

#include <linux/kvm.h>
#include <linux/kvm_para.h>

#define vp_rax    0
#define vp_rbx    1
#define vp_rcx    2
#define vp_rdx    3

#define vp_rsi    4
#define vp_rdi    5

#define vp_rsp    6
#define vp_rbp    7

#define vp_r8     8
#define vp_r9     9
#define vp_r10    10
#define vp_r11    11
#define vp_r12    12
#define vp_r13    13
#define vp_r14    14
#define vp_r15    15

#define vp_rip    16
#define vp_rflags 17

extern obj_trait* vp_reg_t ;
typedef struct    vp_reg   {
    obj             head   ;
    vp_cpu*         cpu    ;
    u64_t*          reg_vec;
    struct kvm_regs reg    ;
}   vp_reg                 ;

bool_t vp_reg_new  (vp_reg*, u32_t, va_list);
bool_t vp_reg_clone(vp_reg*, vp_reg*)       ;
void   vp_reg_del  (vp_reg*)                ;

bool_t vp_reg_get  (vp_reg*, u64_t, u64_t*) ;
bool_t vp_reg_set  (vp_reg*, u64_t, u64_t)  ;

#endif