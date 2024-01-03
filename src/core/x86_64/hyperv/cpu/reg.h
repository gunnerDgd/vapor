#ifndef __CORE_KVM_CPU_REG_H__
#define __CORE_KVM_CPU_REG_H__

#include "../details/cpu/reg.h"

bool_t vp_reg_get(vp_reg*, u64_t, u64_t*);
bool_t vp_reg_set(vp_reg*, u64_t, u64_t) ;

#endif