#include "pio.h"

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