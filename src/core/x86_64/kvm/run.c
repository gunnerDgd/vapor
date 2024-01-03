#include "run.h"

#include "cpu.h"
#include "sys.h"
#include "core.h"

#include <sys/ioctl.h>
#include <errno.h>
#include <stdio.h>

obj_trait vp_run_trait     = {
    .on_new   = &vp_run_new  ,
    .on_clone = &vp_run_clone,
    .on_ref   = 0            ,
    .on_del   = &vp_run_del  ,
    .size     = sizeof(vp_run)
};

obj_trait *vp_run_t = &vp_run_trait;

bool_t
    vp_run_new
        (vp_run* par_run, u32_t par_count, va_list par) {
            if (kvm < 0)        return false_t;
            if (par_count != 1) return false_t;

            par_run->cpu = va_arg(par, vp_cpu*);
            if (!par_run->cpu)                            return false_t;
            if (trait_of(par_run->cpu) != vp_cpu_t)       return false_t;
            if (par_run->cpu->state    != vp_cpu_on)      return false_t;
            if (ioctl(par_run->cpu->cpu, KVM_RUN, 0) < 0) return false_t;

            par_run->cpu->state = vp_cpu_run       ;
            par_run->cpu        = ref(par_run->cpu);
            par_run->run        = par_run->cpu->run;

            return true_t;
}

bool_t
    vp_run_clone
        (vp_run* par, vp_run* par_clone) {
            return false_t;
}

void
    vp_run_del
        (vp_run* par)                                                     {
            if (par->cpu->state == vp_cpu_run) par->cpu->state = vp_cpu_on;
            del(par->run_task);
            del(par->cpu)     ;
}

u64_t
    vp_run_type
        (vp_run* par)                                    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_run_t) return false_t;

            switch(par->cpu->run->exit_reason)        {
                case KVM_EXIT_MMIO: return vp_run_mmio;
                case KVM_EXIT_IO  : return vp_run_pio ;
                case KVM_EXIT_HLT : return vp_run_halt;
                default           : return -1         ;
            }
}

vp_cpu*
    vp_run_cpu
        (vp_run* par)                              {
            if (!par)                      return 0;
            if (trait_of(par) != vp_run_t) return 0;

            return par->cpu;
}

vp_sys*
    vp_run_sys
        (vp_run* par)                              {
            if (!par)                      return 0;
            if (trait_of(par) != vp_run_t) return 0;
            if (!par->cpu)                 return 0;

            return par->cpu->sys;
}

vp_mmu*
    vp_run_mmu
        (vp_run* par)                              {
            if (!par)                      return 0;
            if (trait_of(par) != vp_run_t) return 0;
            if (!par->cpu)                 return 0;
            if (!par->cpu->sys)            return 0;

            return par->cpu->sys->mmu;
}