#ifndef __BASE_KVM_CPU_REG_H__
#define __BASE_KVM_CPU_REG_H__

#include "obj.h"

#define vp_cpu_rax 0
#define vp_cpu_rbx 1
#define vp_cpu_rcx 2
#define vp_cpu_rdx 3

#define vp_cpu_rsi 4
#define vp_cpu_rdi 5

#define vp_cpu_rsp 6
#define vp_cpu_rbp 7

#define vp_cpu_r8  8
#define vp_cpu_r9  9
#define vp_cpu_r10 10
#define vp_cpu_r11 11
#define vp_cpu_r12 12
#define vp_cpu_r13 13
#define vp_cpu_r14 14
#define vp_cpu_r15 15

bool_t vp_get_reg(struct vp_cpu*, u64_t, u64_t*);
bool_t vp_set_reg(struct vp_cpu*, u64_t, u64_t) ;

#endif