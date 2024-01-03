#include "cpu.h"
#include "sys.h"
#include "core.h"

#include <sys/ioctl.h>
#include <sys/mman.h>

obj_trait vp_cpu_trait     = {
    .on_new   = &vp_cpu_new  ,
    .on_clone = &vp_cpu_clone,
    .on_ref   = 0            ,
    .on_del   = &vp_cpu_del  ,
    .size     = sizeof(vp_cpu)
};

obj_trait* vp_cpu_t = &vp_cpu_trait;

bool_t
    vp_cpu_new
        (vp_cpu* par_cpu, u32_t par_count, va_list par) {
            if (kvm < 0)        return false_t;
            if (par_count != 1) return false_t;

            par_cpu->sys = va_arg(par, vp_sys*);
            if (!par_cpu->sys)                      return false_t;
            if (trait_of(par_cpu->sys) != vp_sys_t) return false_t;

            par_cpu->state    = vp_cpu_off                                                 ;
            par_cpu->cpu_id   = par_cpu->sys->cpu_count                                    ;
            par_cpu->cpu      = ioctl (par_cpu->sys->sys, KVM_CREATE_VCPU, par_cpu->cpu_id); if (par_cpu->cpu < 0) return false_t;
            par_cpu->run_size = ioctl (kvm              , KVM_GET_VCPU_MMAP_SIZE, 0)       ;
            par_cpu->run      = mmap  (
                0                     ,
                par_cpu->run_size     ,
                PROT_READ | PROT_WRITE,
                MAP_SHARED            ,
                par_cpu->cpu          ,
                0
            );

            if (!par_cpu->run)           return false_t;
            if (par_cpu->run_size == -1) return false_t;
            if (par_cpu->cpu      == -1) return false_t;
            if(!par_cpu->sys->bsp)                     {
                par_cpu->sys->bsp = ref(par_cpu);
                par_cpu->state    = vp_cpu_on   ;
            }

            par_cpu->sys_hnd = list_push_back(&par_cpu->sys->cpu, par_cpu);
            par_cpu->sys     = ref(par_cpu->sys)                          ;
            par_cpu->sys->cpu_count++                                     ;
            return true_t;
}

bool_t
    vp_cpu_clone
        (vp_cpu* par, vp_cpu* par_clone) {
            return false_t;
}

void
    vp_cpu_del
        (vp_cpu* par)                             {
            munmap  (par->run, par->run_size)     ;
            list_pop(&par->sys->cpu, par->sys_hnd);
}