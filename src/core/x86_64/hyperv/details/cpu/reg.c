#include "reg.h"

#include "../core.h"
#include "../cpu.h"
#include "../node.h"
#include "../root.h"

#include <Windows.h>

WHV_REGISTER_NAME vp_reg_name[] = {
    WHvX64RegisterRax  ,
    WHvX64RegisterRbx  ,
    WHvX64RegisterRcx  ,
    WHvX64RegisterRdx  ,
    WHvX64RegisterRsi  ,
    WHvX64RegisterRdi  ,
    WHvX64RegisterRsp  ,
    WHvX64RegisterRbp  ,
    WHvX64RegisterR8   ,
    WHvX64RegisterR9   ,
    WHvX64RegisterR10  ,
    WHvX64RegisterR11  ,
    WHvX64RegisterR12  ,
    WHvX64RegisterR13  ,
    WHvX64RegisterR14  ,
    WHvX64RegisterR15  ,
    WHvX64RegisterRip  ,
    WHvX64RegisterRflags
};

obj_trait vp_reg_trait     = {
    .on_new   = &vp_reg_new  ,
    .on_clone = &vp_reg_clone,
    .on_ref   = 0            ,
    .on_del   = &vp_reg_del  ,
    .size     = sizeof(vp_reg)
};

obj_trait *vp_reg_t = &vp_reg_trait;

bool_t
    vp_reg_new
        (vp_reg* par_reg, u32_t par_count, va_list par) {
            void *cpu_ptr = va_arg(par, void*);
            if (!cpu_ptr)                  return false_t; vp_cpu* cpu = list_get(cpu_ptr);
            if (!cpu)                      return false_t;
            if (trait_of(cpu) != vp_cpu_t) return false_t;
            if (par_count != 1)            return false_t;

            vp_root* root = cpu->root; if (!root) return false_t;
            vp_node* node = cpu->node; if (!node) return false_t;

            if (trait_of(root) != vp_root_t) return false_t;
            if (trait_of(node) != vp_node_t) return false_t;

            HRESULT res = WHvGetVirtualProcessorRegisters (
                root->root  ,
                cpu->cpu    ,
                vp_reg_name ,
                18          ,
                par_reg->reg
            );

            if (res != S_OK) 
                return false_t;

            par_reg->cpu  = ref(cpu) ;
            par_reg->node = ref(node);
            par_reg->root = ref(root);
            return true_t;
}

bool_t
    vp_reg_clone
        (vp_reg* par, vp_reg* par_clone) {
            return false_t;
}

void
    vp_reg_del
        (vp_reg* par)                       {
            WHvSetVirtualProcessorRegisters (
                par->root->root,
                par->cpu->cpu  ,
                vp_reg_name    ,
                18             ,
                par->reg
            );

            del(par->cpu);
}