#include "mmio.h"

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