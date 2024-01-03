#include "node.h"
#include "root.h"
#include "cpu.h"

obj_trait vp_node_trait     = {
    .on_new   = &vp_node_new  ,
    .on_clone = &vp_node_clone,
    .on_ref   = 0             ,
    .on_del   = &vp_node_del  ,
    .size     = sizeof(vp_node)
};

obj_trait *vp_node_t = &vp_node_trait;

bool_t 
    vp_node_new
        (vp_node* par_node, u32_t par_count, va_list par) {
            vp_root* root      = va_arg(par, vp_root*);
            u64_t    node      = va_arg(par, u64_t)   ;
            u64_t    cpu       = va_arg(par, u64_t)   ;
            u64_t    mmu_begin = va_arg(par, u64_t)   ;
            u64_t    mmu_end   = va_arg(par, u64_t)   ;

            if (par_count != 5)              return false_t;
            if (!root)                       return false_t;
            if (trait_of(root) != vp_root_t) return false_t;

            if (!make_at(&par_node->cpu, list_t)   from(0))                     goto new_failed;
            if (!make_at(&par_node->mmu, vp_mmu_t) from(2, mmu_begin, mmu_end)) goto new_failed;

            for (u64_t i = 0 ; i < cpu; ++i)        {
                vp_cpu* push = make (vp_cpu_t) from (
                    3             ,
                    root          ,
                    par_node      ,
                    node * cpu + i
                );

                if (!push)                                 goto new_failed ;
                if (!list_push_back(&par_node->cpu, push)) goto new_failed ;
                del(push);

                if (!root->bsp)                 {
                    root->bsp = push            ;
                    root->bsp->state = vp_cpu_on;
                }
            }

            par_node->root     = ref(root)     ;
            par_node->mmu.root = par_node->root;
            par_node->mmu.node = par_node      ;
            return true_t;
    new_failed:
            del (&par_node->cpu);
            del (&par_node->mmu);
            return false_t;
}

bool_t
    vp_node_clone
        (vp_node* par, vp_node* par_clone) {
            return false_t;
}

void
    vp_node_del
        (vp_node* par)    {
            del(par->root);

            del(&par->cpu);
            del(&par->mmu);
}