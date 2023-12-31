#include "sys.h"
#include "mmu.h"
#include "core.h"

#include <linux/kvm.h>
#include <linux/kvm_para.h>

#include <unistd.h>
#include <sys/ioctl.h>

obj_trait vp_sys_trait     = {
    .on_new   = &vp_sys_new  ,
    .on_clone = &vp_sys_clone,
    .on_ref   = 0            ,
    .on_del   = &vp_sys_del  ,
    .size     = sizeof(vp_sys)
};

obj_trait *vp_sys_t = &vp_sys_trait;

bool_t 
    vp_sys_new
        (vp_sys* par_sys, u32_t par_count, va_list par) {
            if (par_count > 0) return false_t;
            if (kvm < 0)       return false_t;

            par_sys->cpu_count = 0                                ;
            par_sys->mmu       = make (vp_mmu_t) from (1, par_sys); if (!par_sys->mmu)    return false_t;
            par_sys->sys       = ioctl(kvm, KVM_CREATE_VM, 0)     ; if (par_sys->sys < 0) return false_t;

            if (!make_at (&par_sys->cpu, list_t) from (0)) return false_t;
            return true_t;
}

bool_t
    vp_sys_clone
        (vp_sys* par, vp_sys* par_clone) {
            return false_t;
}

void
    vp_sys_del
        (vp_sys* par)     {
            del(&par->cpu);
            del(par->mmu) ;
}

vp_cpu*
    vp_sys_cpu
        (vp_sys* par, vp_cpu* par_cpu)                 {
            if (!par)                          return 0;
            if (!par_cpu)                      return 0;

            if (trait_of(par)     != vp_sys_t) return 0;
            if (trait_of(par_cpu) != vp_cpu_t) return 0;
            if (par_cpu->sys      != par)      return 0;

            list_elem ret_it = list_next(par_cpu->sys_hnd); if (!ret_it) return 0;
            vp_cpu   *ret    = list_get (ret_it)          ; if (!ret)    return 0;
            return    ret;
}

vp_mmu*
    vp_sys_mmu
        (vp_sys* par)                                    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_sys_t) return false_t;

            return par->mmu;
}