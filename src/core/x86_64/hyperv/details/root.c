#include "root.h"

#include "node.h"
#include "core.h"

obj_trait vp_root_trait     = {
    .on_new   = &vp_root_new  ,
    .on_clone = &vp_root_clone,
    .on_ref   = 0             ,
    .on_del   = &vp_root_del  ,
    .size     = sizeof(vp_root)
};

obj_trait *vp_root_t = &vp_root_trait;

bool_t 
    vp_root_new
        (vp_root* par_root, u32_t par_count, va_list par) {
            u64_t node     = 0        ;
            u64_t node_mmu = (void*)-1;
            u64_t cpu      = 0        ;

            switch (par_count)                                                     {
                case 1 : node = 1                 ; cpu = va_arg(par, u64_t); break;
                case 2 : node = va_arg(par, u64_t); cpu = va_arg(par, u64_t); break;
                default: return false_t;
            }

            if (!node)           return false_t;
            if (!cpu)            return false_t;
            if (node_mmu % node) return false_t; node_mmu /= node;

            HRESULT                prop_res                               ;
            WHV_PARTITION_PROPERTY prop = { .ProcessorCount = node * cpu };

            prop_res = WHvCreatePartition             (&par_root->root); if (prop_res != S_OK) return false_t;
            prop_res = WHvSetPartitionProperty        (
                par_root->root                        ,
                WHvPartitionPropertyCodeProcessorCount,
                &prop,
                sizeof(prop)
            );

            if (prop_res != S_OK)                          return false_t;
            if (WHvSetupPartition(par_root->root) != S_OK) return false_t;

            if (!make_at(&par_root->node, list_t)   from(0))            return false_t;
            if (!make_at(&par_root->port, vp_mmu_t) from(2, 0, 0xFFFF)) return false_t;

            for (u64_t n = 0 ; n < node ; ++n)        {
                vp_node* push = make (vp_node_t) from (
                    5                ,
                    par_root         ,
                    n                ,
                    cpu              ,
                    node_mmu *  n    ,
                    node_mmu * (n + 1)
                );

                if (!push)                                  return false_t;
                if (!list_push_back(&par_root->node, push)) return false_t;
                del(push);
            }

            par_root->port.node = 0       ;
            par_root->port.root = par_root;
            return true_t;
}

bool_t
    vp_root_clone
        (vp_root* par, vp_root* par_clone) {
            return false_t;
}

void
    vp_root_del
        (vp_root* par)     {
            del(&par->node);
            del(&par->port);
}