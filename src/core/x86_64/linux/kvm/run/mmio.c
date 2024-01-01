#include "mmio.h"
#include "../map/mmio.h"

#include "../run.h"
#include "../cpu.h"
#include "../mmu.h"
#include "../sys.h"

obj_trait vp_mmio_trait     = {
    .on_new   = &vp_mmio_new  ,
    .on_clone = &vp_mmio_clone,
    .on_ref   = 0             ,
    .on_del   = &vp_mmio_del  ,
    .size     = sizeof(vp_mmio)
};

obj_trait *vp_mmio_t = &vp_mmio_trait;

bool_t
    vp_mmio_new
        (vp_mmio* par_mmio, u32_t par_count, va_list par) {
            par_mmio->run = va_arg(par, vp_run*);
            if (!par_mmio->run)                    return false_t;
            if (trait_of(par_mmio) != vp_run_t)    return false_t; struct kvm_run* run = par_mmio->run->run;
            if (run->exit_reason != KVM_EXIT_MMIO) return false_t;

            par_mmio->dir  = run->mmio.is_write ;
            par_mmio->addr = run->mmio.phys_addr;
            par_mmio->size = run->mmio.len      ;
            par_mmio->data = run->mmio.data     ;
            par_mmio->run  = ref(par_mmio->run);

            return true_t;
}

bool_t
    vp_mmio_clone
        (vp_mmio* par, vp_mmio* par_clone) {
            return false_t;
}

void
    vp_mmio_del
        (vp_mmio* par)                                          {
            vp_mmu* mmu = vp_run_mmu (par->run)                 ; if (!mmu) return;
            vp_map* map = vp_mmu_find(mmu, par->addr, par->size); if (!map) return;
            switch (par->dir)                                   {
            case vp_mmio_in :
                if (par->size == 1) { vp_mmio_rd8 (map, par->addr, par->data); return; }
                if (par->size == 2) { vp_mmio_rd16(map, par->addr, par->data); return; }
                if (par->size == 4) { vp_mmio_rd32(map, par->addr, par->data); return; }
                if (par->size == 8) { vp_mmio_rd64(map, par->addr, par->data); return; }
                break;
            case vp_mmio_out:
                if (par->size == 1) { vp_mmio_wr8 (map, par->addr, par->data); return; }
                if (par->size == 2) { vp_mmio_wr16(map, par->addr, par->data); return; }
                if (par->size == 4) { vp_mmio_wr32(map, par->addr, par->data); return; }
                if (par->size == 8) { vp_mmio_wr64(map, par->addr, par->data); return; }
                break;
            default         : return;
            }

            par->run->run_task = 0;
            del (par->run);
}

u64_t
    vp_mmio_dir
        (vp_mmio* par)                               {
            if (!par)                       return -1;
            if (trait_of(par) != vp_mmio_t) return -1;

            return par->dir;
}

u64_t
    vp_mmio_addr
        (vp_mmio* par)                               {
            if (!par)                       return -1;
            if (trait_of(par) != vp_mmio_t) return -1;

            return par->addr;
}

u64_t
    vp_mmio_size
        (vp_mmio* par)                                 {
            if (!par)                       return 0ull;
            if (trait_of(par) != vp_mmio_t) return 0ull;

            return par->size;
}