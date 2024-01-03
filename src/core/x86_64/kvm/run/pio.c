#include "pio.h"
#include "../map/pio.h"

#include "../run.h"
#include "../cpu.h"
#include "../mmu.h"

obj_trait vp_pio_trait     = {
    .on_new   = &vp_pio_new  ,
    .on_clone = &vp_pio_clone,
    .on_ref   = 0            ,
    .on_del   = &vp_pio_del  ,
    .size     = sizeof(vp_pio)
};

obj_trait *vp_pio_t = &vp_pio_trait;

bool_t
    vp_pio_new
        (vp_pio* par_pio, u32_t par_count, va_list par) {
            par_pio->run = va_arg(par, vp_run*);
            if (!par_pio->run)                      return false_t;
            if (trait_of(par_pio->run) != vp_run_t) return false_t; struct kvm_run* run = par_pio->run->run;
            if (run->exit_reason != KVM_EXIT_IO)    return false_t;

            par_pio->addr = run->io.port                       ;
            par_pio->dir  = run->io.direction                  ;
            par_pio->size = run->io.size                       ;
            par_pio->data = run->io.data_offset + (u8_t*)run   ;
            par_pio->run  = ref(par_pio->run);

            return true_t;
}

bool_t
    vp_pio_clone
        (vp_pio* par, vp_pio* par_clone) {
            return false_t;
}

void
    vp_pio_del
        (vp_pio* par)                                                                {
            vp_mmu* mmu = vp_run_mmu      (par->run)         ; if (!mmu) goto del_ret;
            vp_map* map = vp_mmu_find_port(mmu, par->addr, 1); if (!map) goto del_ret;

            switch (par->dir) {
            case vp_pio_in :
                if (par->size == 1) { vp_pio_rd8 (map, par->addr, par->data); goto del_ret; }
                if (par->size == 2) { vp_pio_rd16(map, par->addr, par->data); goto del_ret; }
                if (par->size == 4) { vp_pio_rd32(map, par->addr, par->data); goto del_ret; }
                break;
            case vp_pio_out:
                if (par->size == 1) { vp_pio_wr8 (map, par->addr, par->data); goto del_ret; }
                if (par->size == 2) { vp_pio_wr16(map, par->addr, par->data); goto del_ret; }
                if (par->size == 4) { vp_pio_wr32(map, par->addr, par->data); goto del_ret; }
                break;
            default : goto del_ret;
            }
    del_ret:
            par->run->run_task = 0;
            del (par->run);
}

u64_t
    vp_pio_dir
        (vp_pio* par)                               {
            if (!par)                      return -1;
            if (trait_of(par) != vp_pio_t) return -1;

            return par->dir;
}

u64_t
    vp_pio_addr
        (vp_pio* par)                               {
            if (!par)                      return -1;
            if (trait_of(par) != vp_pio_t) return -1;

            return par->addr;
}

u64_t
    vp_pio_size
        (vp_pio* par)                                 {
            if (!par)                      return 0ull;
            if (trait_of(par) != vp_pio_t) return 0ull;

            return par->size;
}