#include "mmu.h"
#include "sys.h"
#include "core.h"

#include "map.h"
#include "map_key.h"

#include "map/mmio.h"
#include "map/pio.h"

#include <sys/ioctl.h>

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
            if (kvm < 0)        return false_t;
            if (par_count != 1) return false_t;

            par_mmu->sys = va_arg(par, vp_sys*);
            if (!par_mmu->sys)                                          return false_t;
            if (trait_of(par_mmu->sys) != vp_sys_t)                     return false_t;
            if (!make_at(&par_mmu->mmu , map_t) from (1, vp_map_key_t)) return false_t;
            if (!make_at(&par_mmu->port, map_t) from (1, vp_map_key_t)) {
                del(&par_mmu->mmu);
                return false_t;
            }

            par_mmu->sys = ref(par_mmu->sys);
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
            del(par->sys) ;
            del(&par->mmu);
}

struct vp_map*
    vp_mmu_map
        (vp_mmu* par, struct vp_map* par_map)          {
            if (!par)                          return 0;
            if (!par_map)                      return 0;

            if (trait_of(par)     != vp_mmu_t) return 0;
            if (trait_of(par_map) != vp_map_t) return 0;

            if (par_map->mmu)                  return 0;
            if (par_map->mmu_hnd)              return 0;

            if (vp_map_none(par_map)) return 0;
            if (vp_map_pio (par_map)) par_map->mmu_hnd = map_push(&par->port, par_map);
            if (vp_map_mmio(par_map)) par_map->mmu_hnd = map_push(&par->mmu , par_map);
            if (vp_map_mem (par_map))                                                   {
                par_map->mem.slot = par->slot;
                if (ioctl(par->sys->sys, KVM_SET_USER_MEMORY_REGION, &par_map->mem) < 0)
                    return 0;

                par_map->mmu_hnd  = map_push(&par->mmu, par_map);
                par->slot++;
            }

            if (!par_map->mmu_hnd) return 0;
            par_map->mmu = ref(par);
            return par_map;
}

struct vp_map*
    vp_mmu_find
        (vp_mmu* par, u64_t par_addr, u64_t par_len) {
            if (!par)                      return 0;
            if (trait_of(par) != vp_mmu_t) return 0;

            vp_map key;
            if (!make_at (&key, vp_map_t) from (2, par_addr, par_addr + par_len))
                return 0;

            map_elem ret_it = map_find(&par->mmu, &key); if (ret_it == map_end(&par->mmu)) return 0;
            vp_map  *ret    = map_get (ret_it)         ; if (!ret)                         return 0;
            return   ret;
}

struct vp_map*
    vp_mmu_find_port
        (vp_mmu* par, u64_t par_addr, u64_t par_len) {
            if (!par)                      return 0;
            if (trait_of(par) != vp_mmu_t) return 0;

            vp_map key;
            if (!make_at (&key, vp_map_t) from (2, par_addr, par_addr + par_len))
                return 0;

            map_elem ret_it = map_find(&par->port, &key); if (ret_it == map_end(&par->port)) return 0;
            vp_map  *ret    = map_get (ret_it)          ; if (!ret)                          return 0;
            return   ret;
}