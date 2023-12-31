#ifndef __DETAILS_HV_MMU_H__
#define __DETAILS_HV_MMU_H__

#include "obj.h"
#include "list.h"

extern obj_trait* mmu_t;
typedef struct    mmu  {
    obj         head;
    struct sys *sys ;
    struct map *map ;
}   mmu;

bool_t      mmu_new   (mmu*, u32_t, va_list);
bool_t      mmu_clone (mmu*, mmu*)          ;
void        mmu_del   (mmu*)                ;

struct map* mmu_map       (mmu*, struct map*) ;
struct map* mmu_find      (mmu*, u64_t)       ;
struct map* mmu_find_range(mmu*, u64_t, u64_t);

#endif