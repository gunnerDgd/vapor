#include "mmu.h"

#include "sys.h"
#include "map.h"

bool_t      
    mmu_new
        (mmu* par_mmu, u32_t par_count, va_list par) {
            par_mmu->sys = va_arg(par, sys*);
            if (!par_mmu->sys)                   return false_t;
            if (trait_of(par_mmu->sys) != sys_t) return false_t;

            par_mmu->map = make (map_t) from (2, 0, (void*)-1); if (!par_mmu->map) return false_t;
            par_mmu->sys = ref(par_mmu->sys)                  ;

            return true_t;
}

bool_t
    mmu_clone
        (mmu* par, mmu* par_clone) {
            return false_t;
}

void
    mmu_del
        (mmu* par)       {
            del(par->sys);
            del(par->map);
}

struct map*
    mmu_map
        (mmu* par, struct map* par_map) {
            if (!par)     return false_t;
            if (!par_map) return false_t;

            if (trait_of(par)     != mmu_t) return false_t;
            if (trait_of(par_map) != map_t) return false_t;

            return map_sub(par->map, par_map);
}

struct map*
    mmu_find
        (mmu* par, u64_t par_addr)                 {
            return mmu_find_range(par, par_addr, 0);
}

struct map*
    mmu_find_range
        (mmu* par, u64_t par_addr, u64_t par_len) {
            if (!par)                   return 0;
            if (trait_of(par) != mmu_t) return 0;

            map   *ret = map_find(par->map, par_addr, par_len);
            while (ret)                                        {
                map *ret_sub = map_find(ret, par_addr, par_len);
                if (!ret_sub) return ret;

                ret = ret_sub;
            }

            return ret;
}