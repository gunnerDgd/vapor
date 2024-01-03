#include "halt.h"

#include "../cpu.h"
#include "../node.h"
#include "../root.h"

obj_trait vp_halt_trait     = {
    .on_new   = &vp_halt_new  ,
    .on_clone = &vp_halt_clone,
    .on_ref   = 0             ,
    .on_del   = &vp_halt_del  ,
    .size     = sizeof(vp_halt)
};

obj_trait *vp_halt_t = &vp_halt_trait;

bool_t
    vp_halt_new
        (vp_halt* par_halt, u32_t par_count, va_list par) {
            vp_cpu *cpu = va_arg(par, vp_cpu*);
            if (!cpu)                                             return false_t;
            if (trait_of(cpu) != vp_cpu_t)                        return false_t;
            if (cpu->run.ExitReason != WHvRunVpExitReasonX64Halt) return false_t;
            
            vp_node* node = cpu->node; if (!node) return false_t;
            vp_root* root = cpu->root; if (!root) return false_t;

            if (trait_of(node) != vp_node_t) return false_t;
            if (trait_of(root) != vp_root_t) return false_t;
            
            par_halt->cpu  = ref(cpu) ;
            par_halt->node = ref(node);
            par_halt->root = ref(root);
            
            return true_t;
}

bool_t
    vp_halt_clone
        (vp_halt* par, vp_halt* par_clone) {
            return false_t;
}

void
    vp_halt_del
        (vp_halt* par)                     {
            par->cpu->state    = vp_cpu_off;
            par->cpu->run_task = 0         ;
            
            del(par->cpu) ;
            del(par->node);
            del(par->root);
}