#include "map.h"
#include "map_key.h"

#include "mmu.h"
#include "core.h"

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
            if (par_count != 2) return false_t;

            par_map->type  = vp_map_type_none             ;
            par_map->begin = va_arg(par, u64_t)           ;
            par_map->end   = va_arg(par, u64_t)           ;
            par_map->size  = par_map->end - par_map->begin; if (par_map->begin >= par_map->end) return false_t;
            par_map->end  -= 1                            ;
            return true_t;
}

bool_t 
    vp_map_clone
        (vp_map* par, vp_map* par_clone) {
            return false_t;
}

void
    vp_map_del
        (vp_map* par)                                      {
            if (par->map_ops) par->map_ops->unmap(par->map);
            del(par->mmu);
}