#include "mmu.h"

#include "core.h"
#include "node.h"
#include "root.h"

#include "map.h"
#include "map_key.h"

obj_trait vp_mmu_trait     = {
    .on_new   = &vp_mmu_new  ,
    .on_clone = &vp_mmu_clone,
    .on_ref   = 0            ,
    .on_del   = &vp_mmu_del  ,
    .size     = sizeof(vp_mmu)
};

obj_trait *vp_mmu_t = &vp_mmu_trait;

bool_t
    vp_mmu_new
        (vp_mmu* par_mmu, u32_t par_count, va_list par) {
            par_mmu->begin = va_arg (par, u64_t);
            par_mmu->end   = va_arg (par, u64_t);

            if (par_count != 2)                                         return false_t;
            if (par_mmu->begin >= par_mmu->end)                         return false_t;
            if (!make_at(&par_mmu->mmu , map_t) from (1, vp_map_key_t)) return false_t;

            return true_t;
}

bool_t
    vp_mmu_clone
        (vp_mmu* par, vp_mmu* par_clone) {
            return false_t;
}

void
    vp_mmu_del
        (vp_mmu* par)     {
            del(&par->mmu);
}

void*
    vp_mmu_map
        (vp_mmu* par, vp_map* par_map)                 {
            if (!par)                          return 0;
            if (!par_map)                      return 0;

            if (trait_of(par)     != vp_mmu_t) return 0;
            if (trait_of(par_map) != vp_map_t) return 0;

            if (par_map->begin < par->begin)   return 0;
            if (par_map->end   > par->end)     return 0;

            void *ret = map_push(&par->mmu, par_map); 
            if  (!ret) return 0;

            par_map->map_ops = 0       ;
            par_map->map     = 0       ;
            par_map->mmu     = ref(par);
            return ret;
}

void*
    vp_mmu_find
        (vp_mmu* par, u64_t par_addr, u64_t par_len) {
            if (!par)                      return 0;
            if (trait_of(par) != vp_mmu_t) return 0;

            vp_map key;
            if (!make_at (&key, vp_map_t) from (2, par_addr, par_addr + par_len))
                return 0;

            void*  ret = map_find(&par->mmu, &key); if (ret == map_end(&par->mmu)) return 0;
            return ret;
}