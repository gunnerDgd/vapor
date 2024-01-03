#include "reg.h"
#include "../core.h"

#include <linux/kvm.h>
#include <linux/kvm_para.h>
#include <sys/ioctl.h>

obj_trait vp_reg_trait     = {
    .on_new   = &vp_reg_new  ,
    .on_clone = &vp_reg_clone,
    .on_ref   = 0            ,
    .on_del   = &vp_reg_del  ,
    .size     = sizeof(vp_reg)
};

obj_trait *vp_reg_t = &vp_reg_trait;

bool_t
    vp_reg_new
        (vp_reg* par_reg, u32_t par_count, va_list par) {
            if (kvm < 0)        return false_t;
            if (par_count != 1) return false_t;

            par_reg->cpu = va_arg(par, vp_cpu*);
            if (!par_reg->cpu)                                             return false_t;
            if (trait_of(par_reg->cpu) != vp_cpu_t)                        return false_t;
            if (ioctl(par_reg->cpu->cpu, KVM_GET_REGS, &par_reg->reg) < 0) return false_t;

            par_reg->cpu     = ref(par_reg->cpu);
            par_reg->reg_vec = &par_reg->reg    ;
            return true_t;
}

bool_t
    vp_reg_clone
        (vp_reg* par, vp_reg* par_clone) {
            return false_t;
}

void
    vp_reg_del
        (vp_reg* par)                                    {
            ioctl(par->cpu->cpu, KVM_SET_REGS, &par->reg);
            del  (par->cpu);
}

bool_t
    vp_reg_get
        (vp_reg* par, u64_t par_reg, u64_t* par_get)     {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_reg_t) return false_t;
            if (par_reg > vp_rflags)       return false_t;

            *par_get = par->reg_vec[par_reg];
            return true_t;
}

bool_t
    vp_reg_set
        (vp_reg* par, u64_t par_reg, u64_t par_set)      {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_reg_t) return false_t;
            if (par_reg > vp_rflags)       return false_t;

            par->reg_vec[par_reg] = par_set;
            return true_t;
}