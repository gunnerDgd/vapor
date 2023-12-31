#include "cpu.h"
#include "sys.h"

#include <WinHvPlatform.h>
#include <WinHvPlatformDefs.h>
#include <Windows.h>

bool_t      
    vcpu_new
        (vcpu* par_vcpu, u32_t par_count, va_list par) {
            par_vcpu->sys = va_arg(par, sys*);
            if (!par_vcpu->sys)                                                                      return false_t;
            if (trait_of(par_vcpu->sys) != sys_t)                                                    return false_t; ++par_vcpu->sys->vcpu_count;
            if (!WHvCreateVirtualProcessor(par_vcpu->sys_hnd, par_vcpu->sys->vcpu_count, 0) != S_OK) return false_t;

            par_vcpu->sys_hnd = list_push_back(&par_vcpu->sys->vcpu, par_vcpu);
            par_vcpu->sys     = ref(par_vcpu->sys);

            return true_t;
}

bool_t
    vcpu_clone
        (vcpu* par, vcpu* par_clone) {
            return false_t;
}

void
    vcpu_del
        (vcpu* par)                                            {
            WHvDeleteVirtualProcessor(par->sys->sys, par->vcpu);
            del(par->sys);
}

struct run* 
    vcpu_run
        (vcpu* par)                              {
            if (!par)                    return 0;
            if (trait_of(par) != vcpu_t) return 0;
}