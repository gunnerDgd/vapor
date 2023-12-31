#include "mem.h"

bool_t
    vp_mem_map
        (vp_map* par, void* par_mem, u64_t par_size)     {
            if (!par)                      return false_t;
            if (!par_mem)                  return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (par->size != par_size)     return false_t;

            par->ops.mem = par_mem;
            return true_t;
}