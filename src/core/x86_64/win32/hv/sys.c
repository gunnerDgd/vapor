#include "sys.h"
#include "mmu.h"

#include <Windows.h>

#include <WinHvPlatform.h>
#include <WinHvPlatformDefs.h>

bool_t 
    sys_new
        (sys* par_sys, u32_t par_count, va_list par)                     {
            if (!make_at(&par_sys->vcpu, list_t) from (0)) return false_t;
            if (WHvCreatePartition(&par_sys->sys) != S_OK) return false_t;

            par_sys->mmu = make (mmu_t) from (0);
            if (!par_sys->mmu)
                return false_t;

            return true_t;
    new_failed:
            del (&par_sys->vcpu);
            return false_t;
}

bool_t sys_clone(sys*, sys*);
void   sys_del(sys*, sys*);