#include "run.h"

#include "cpu.h"
#include "sys.h"
#include "core.h"

#include <sys/ioctl.h>

bool_t
    vp_run_new
        (vp_run* par_run, u32_t par_count, va_list par) {
            if (kvm < 0)        return false_t;
            if (par_count != 1) return false_t;

            par_run->cpu = va_arg(par, vp_cpu*);
            if (!par_run->cpu)                       return false_t;
            if (trait_of(par_run->cpu) != vp_cpu_t)  return false_t;
            if (par_run->cpu->state    != vp_cpu_on) return false_t;

            par_run->cpu        = ref(par_run->cpu)     ;
            par_run->cpu->state = vp_cpu_run            ;
            par_run->sys        = ref(par_run->cpu->sys);
            par_run->mmu        = ref(par_run->sys->mmu);

            if (ioctl(par_run->cpu->cpu, KVM_RUN, par_run->cpu->run) < 0)
                goto new_failed;

            par_run->cpu->state = vp_cpu_run;
            return true_t;

    new_failed:
            del (par_run->cpu);
            del (par_run->sys);
            del (par_run->mmu);

            return false_t;
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
            del(par->cpu);
            del(par->sys);
            del(par->mmu);
            del(par->run);
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