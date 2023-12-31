#include "pio.h"
#include "../map/pio.h"

#include "../run.h"
#include "../cpu.h"
#include "../mmu.h"

bool_t
    vp_pio_new
        (vp_pio* par_pio, u32_t par_count, va_list par) {
            par_pio->run = va_arg(par, vp_run*);
            if (!par_pio->run)          return false_t;
            if (trait_of(par_pio->run)) return false_t;

            par_pio->addr =       par_pio->run->cpu->run->io.port       ;
            par_pio->dir  =       par_pio->run->cpu->run->io.direction  ;
            par_pio->size =       par_pio->run->cpu->run->io.size       ; u8_t* run = par_pio->run->run;
            par_pio->data = run + par_pio->run->cpu->run->io.data_offset;

            par_pio->map  = vp_mmu_find_range(par_pio->run->mmu, par_pio->addr, par_pio->size);
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
        (vp_pio* par)         {
            switch (par->dir) {
            case vp_pio_in :
                if (par->size == 1) { vp_pio_rd8 (par->map, par->addr, par->data); return; }
                if (par->size == 2) { vp_pio_rd16(par->map, par->addr, par->data); return; }
                if (par->size == 4) { vp_pio_rd32(par->map, par->addr, par->data); return; }
                break;
            case vp_pio_out:
                if (par->size == 1) { vp_pio_wr8 (par->map, par->addr, par->data); return; }
                if (par->size == 2) { vp_pio_wr16(par->map, par->addr, par->data); return; }
                if (par->size == 4) { vp_pio_wr32(par->map, par->addr, par->data); return; }
                break;
            default         : return;
            }

            par->run->run = 0;
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