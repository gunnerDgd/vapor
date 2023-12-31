#include "mmu.h"

#include "sys.h"
#include "map.h"
#include "map/mmio.h"
#include "map/pio.h"

#include "core.h"

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
            if (!par_mmu->sys)                      return false_t;
            if (trait_of(par_mmu->sys) != vp_sys_t) return false_t;

            par_mmu->map_count = 0;
            par_mmu->map       = make (vp_map_t) from (2, 0, (void*)-1); if (!par_mmu->map) goto new_failed;
            par_mmu->sys       = ref(par_mmu->sys)                     ; if (!par_mmu->sys) goto new_failed;
            return true_t;
    new_failed:
            del (par_mmu->sys);
            del (par_mmu->map);

            return false_t;
}

bool_t
    vp_mmu_clone
        (vp_mmu* par, vp_mmu* par_clone) {
            return false_t;
}

void
    vp_mmu_del
        (vp_mmu* par)    {
            del(par->sys);
            del(par->map);
}

struct vp_map*
    vp_mmu_map
        (vp_mmu* par, struct vp_map* par_map) {
            if (!par)     return false_t;
            if (!par_map) return false_t;

            if (trait_of(par)     != vp_mmu_t) return false_t;
            if (trait_of(par_map) != vp_map_t) return false_t;

            vp_map *ret = vp_map_sub(par->map, par_map);
            if (!ret) return 0;
            if (vp_map_mmio(ret)) ret->ops.ops_mmio->map(ret->ops.mmio, ret);
            if (vp_map_pio (ret)) ret->ops.ops_pio ->map(ret->ops.pio , ret);
            if (vp_map_mem (ret))                          {
                ret->map.slot            = par->map_count  ;
                ret->map.guest_phys_addr = par_map->begin  ;
                ret->map.userspace_addr  = par_map->ops.mem;
                if (ioctl(par->sys->sys, KVM_SET_USER_MEMORY_REGION, &ret->map) < 0)
                    return 0;
            }

            return ret;
}

struct vp_map*
    vp_mmu_find
        (vp_mmu* par, u64_t par_addr)                 {
            return vp_mmu_find_range(par, par_addr, 0);
}

struct vp_map*
    vp_mmu_find_range
        (vp_mmu* par, u64_t par_addr, u64_t par_len) {
            if (!par)                      return 0;
            if (trait_of(par) != vp_mmu_t) return 0;

            vp_map* ret = par->map;
            for ( ; ret ; ret = vp_map_find(ret, par_addr, par_len)) {
                if (vp_map_sect(ret)) continue;
                return ret;
            }

            return 0;
}