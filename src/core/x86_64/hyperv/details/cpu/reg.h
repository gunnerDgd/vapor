#ifndef __CORE_KVM_DETAILS_CPU_REG_H__
#define __CORE_KVM_DETAILS_CPU_REG_H__

#include "../core.h"

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

extern obj_trait* vp_reg_t    ;
typedef struct    vp_reg      {
    obj                head   ;
    struct vp_cpu     *cpu    ;
    struct vp_root    *root   ;
    struct vp_node    *node   ;
    WHV_REGISTER_VALUE reg[18];
}   vp_reg;

bool_t vp_reg_new  (vp_reg*, u32_t, va_list);
bool_t vp_reg_clone(vp_reg*, vp_reg*)       ;
void   vp_reg_del  (vp_reg*)                ;

#endif