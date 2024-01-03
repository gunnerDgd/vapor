#ifndef __CORE_HYPERV_DETAILS_ROOT_H__
#define __CORE_HYPERV_DETAILS_ROOT_H__

#include <obj.h>

#include <list.h>
#include <map.h>

#include "mmu.h"
#include "cpu.h"

extern obj_trait *vp_root_t;
typedef struct    vp_root  {
    obj     head;
    void*   root;
    list    node;
    vp_mmu  port;
    vp_cpu* bsp ;
}   vp_root;

bool_t  vp_root_new  (vp_root*, u32_t, va_list);
bool_t  vp_root_clone(vp_root*, vp_root*)      ;
void    vp_root_del  (vp_root*)                ;

#endif