#include "mem.h"
#include "../mmu.h"
#include "../sys.h"

#include <sys/ioctl.h>

bool_t
    vp_mem_map
        (vp_map* par, void* par_mem, u64_t par_size)     {
            if (!par)                      return false_t;
            if (!par_mem)                  return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!vp_map_none(par))         return false_t;
            if (par->size != par_size)     return false_t;

            par->mem.userspace_addr  = par_mem   ;
            par->mem.memory_size     = par_size  ;
            par->mem.guest_phys_addr = par->begin;
            return true_t;
}