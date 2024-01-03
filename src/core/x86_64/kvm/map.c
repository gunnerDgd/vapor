#include "map.h"
#include "map_key.h"

#include "mmu.h"

#include "core.h"
#include "map/mmio.h"
#include "map/pio.h"

obj_trait vp_map_trait     = {
    .on_new   = &vp_map_new  ,
    .on_clone = &vp_map_clone,
    .on_ref   = 0            ,
    .on_del   = &vp_map_del  ,
    .size     = sizeof(vp_map)
};

obj_trait *vp_map_t = &vp_map_trait;

bool_t 
    vp_map_new
        (vp_map* par_map, u32_t par_count, va_list par) {
            if (kvm < 0)        return false_t;
            if (par_count != 2) return false_t;

            par_map->begin = va_arg(par, u64_t)           ;
            par_map->end   = va_arg(par, u64_t)           ;
            par_map->size  = par_map->end - par_map->begin;

            if (par_map->begin >= par_map->end) return false_t;
            return true_t;
}

bool_t 
    vp_map_clone
        (vp_map* par, vp_map* par_clone) {
            return false_t;
}

bool_t
    vp_map_del
        (vp_map* par)    {
            del(par->mmu);
}

bool_t
    vp_map_none
        (vp_map* par)                                    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;

            if (vp_map_pio (par))          return false_t;
            if (vp_map_mmio(par))          return false_t;
            if (vp_map_mem (par))          return false_t;

            return true_t;
}

bool_t
    vp_map_mmio
        (vp_map* par)                                    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map)                 return false_t;
            if (!par->map_ops.mmio)        return false_t;

            return true_t;
}

bool_t
    vp_map_pio
        (vp_map* par)                                    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map)                 return false_t;
            if (!par->map_ops.pio)         return false_t;

            return true_t;
}

bool_t
    vp_map_mem
        (vp_map* par)                                    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;

            if (vp_map_mmio(par))          return false_t;
            if (vp_map_pio (par))          return false_t;
            if (!par->mem.userspace_addr)  return false_t;
            if (!par->mem.memory_size)     return false_t;

            return true_t;
}

u64_t
    vp_map_begin
        (vp_map* par)                               {
            if (!par)                      return -1;
            if (trait_of(par) != vp_map_t) return -1;

            return par->begin;
}

u64_t
    vp_map_end
        (vp_map* par)                               {
            if (!par)                      return -1;
            if (trait_of(par) != vp_map_t) return -1;

            return par->end;
}

u64_t
    vp_map_size
        (vp_map* par)                              {
            if (!par)                      return 0;
            if (trait_of(par) != vp_map_t) return 0;

            return par->size;
}