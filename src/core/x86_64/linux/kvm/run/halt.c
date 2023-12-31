#include "halt.h"

#include "../run.h"
#include "../cpu.h"

bool_t
    vp_halt_new
        (vp_halt* par_halt, u32_t par_count, va_list par) {
            par_halt->run = va_arg(par, vp_run*);
            if (!par_halt->run)                      return false_t;
            if (trait_of(par_halt->run) != vp_run_t) return false_t;

            par_halt->cpu = ref(par_halt->cpu);
            return true_t;
}

bool_t
    vp_halt_clone
        (vp_halt* par, vp_halt* par_clone) {
            return false_t;
}

void
    vp_halt_del
        (vp_halt* par)                  {
            par->cpu->state = vp_cpu_off;
            par->run->run   = 0         ;
            del(par->cpu);
            del(par->run);
}

struct vp_cpu*
    vp_halt_cpu
        (vp_halt* par)                                    {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_halt_t) return false_t;

            return par->cpu;
}