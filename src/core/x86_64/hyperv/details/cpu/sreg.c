#include "sreg.h"

#include "../node.h"
#include "../root.h"
#include "../cpu.h"

WHV_REGISTER_NAME vp_sreg_name[] = {
    WHvX64RegisterCs  ,
    WHvX64RegisterDs  ,
    WHvX64RegisterEs  ,
    WHvX64RegisterFs  ,
    WHvX64RegisterGs  ,
    WHvX64RegisterSs  ,
    WHvX64RegisterTr  ,
    WHvX64RegisterLdtr,
    
    WHvX64RegisterGdtr,
    WHvX64RegisterIdtr
};

obj_trait vp_sreg_trait     = {
    .on_new   = &vp_sreg_new  ,
    .on_clone = &vp_sreg_clone,
    .on_ref   = 0             ,
    .on_del   = &vp_sreg_del  ,
    .size     = sizeof(vp_sreg)
};

obj_trait *vp_sreg_t = &vp_sreg_trait;

bool_t
    vp_sreg_new
        (vp_sreg* par_sreg, u32_t par_count, va_list par) {
            void* cpu_ptr = va_arg(par, void*);
            if (!cpu_ptr)                  return false_t; vp_cpu* cpu = list_get(cpu_ptr);
            if (!cpu)                      return false_t;
            if (trait_of(cpu) != vp_cpu_t) return false_t;
            if (par_count != 1)            return false_t;

            vp_root* root = cpu->root; if (!root) return false_t;
            vp_node* node = cpu->node; if (!node) return false_t;

            if (trait_of(root) != vp_root_t) return false_t;
            if (trait_of(node) != vp_node_t) return false_t;

            HRESULT res = WHvGetVirtualProcessorRegisters (
                root->root    ,
                cpu->cpu      ,
                vp_sreg_name  ,
                10            ,
                par_sreg->sreg
            );

            par_sreg->cpu  = ref(cpu) ;
            par_sreg->node = ref(node);
            par_sreg->root = ref(root);
            return true_t;
}

bool_t
    vp_sreg_clone
        (vp_sreg* par, vp_sreg* par_clone) {
            return false_t;
}

void
    vp_sreg_del
        (vp_sreg* par)                     {
            WHvSetVirtualProcessorRegisters(
                par->root->root,
                par->cpu->cpu  ,
                vp_sreg_name   ,
                10             ,
                par->sreg
            );

            del (par->cpu) ;
            del (par->root);
            del (par->node);
}

