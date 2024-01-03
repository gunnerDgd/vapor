#ifndef __CORE_HYPERV_DETAILS_NODE_H__
#define __CORE_HYPERV_DETAILS_NODE_H__

#include <list.h>
#include "mmu.h"

extern obj_trait* vp_node_t;
typedef struct    vp_node  {
    obj             head;
    struct vp_root* root;
    vp_mmu          mmu ;
    list            cpu ;
}   vp_node;

bool_t  vp_node_new  (vp_node*, u32_t, va_list);
bool_t  vp_node_clone(vp_node*, vp_node*)      ;
void    vp_node_del  (vp_node*)                ;

#endif