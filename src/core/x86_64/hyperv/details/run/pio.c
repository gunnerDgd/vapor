#include "pio.h"

#include "../root.h"
#include "../../root.h"

#include "../node.h"
#include "../../node.h"

#include "../map.h"
#include "../../map.h"

#include "../cpu.h"
#include "../mmu.h"

obj_trait vp_pio_trait     = {
    .on_new   = &vp_pio_new  ,
    .on_clone = &vp_pio_clone,
    .on_ref   = 0            ,
    .on_del   = &vp_pio_del  ,
    .size     = sizeof(vp_pio)
};

obj_trait *vp_pio_t = &vp_pio_trait;

bool_t
    vp_pio_new
        (vp_pio* par_pio, u32_t par_count, va_list par) {
            vp_cpu *cpu = va_arg(par, vp_cpu*);
            if (!cpu)                                                     return false_t;
            if (trait_of(cpu) != vp_cpu_t)                                return false_t;
            if (cpu->run.ExitReason != WHvRunVpExitReasonX64IoPortAccess) return false_t;

            vp_root* root = cpu->root; if (!root) return false_t;
            vp_node* node = cpu->node; if (!node) return false_t;

            if (trait_of(root) != vp_root_t) return false_t;
            if (trait_of(node) != vp_node_t) return false_t;

            par_pio->addr =  cpu->run.IoPortAccess.PortNumber           ;
            par_pio->dir  =  cpu->run.IoPortAccess.AccessInfo.IsWrite   ;
            par_pio->size =  cpu->run.IoPortAccess.AccessInfo.AccessSize;
            par_pio->data = &cpu->run.IoPortAccess.Rax                  ;

            par_pio->cpu  = ref(cpu) ;
            par_pio->root = ref(root);
            par_pio->node = ref(node);
            return true_t;
}

bool_t
    vp_pio_clone
        (vp_pio* par, vp_pio* par_clone) {
            return false_t;
}

void
    vp_pio_del
        (vp_pio* par)                                          {
            WHV_EMULATOR_STATUS res_state                      ;
            HRESULT             res = WHvEmulatorTryIoEmulation(
                par->cpu->emu             ,
                par                       ,
               &par->cpu->run.VpContext   ,
               &par->cpu->run.IoPortAccess,
               &res_state
            );

            par->cpu->run_task = 0        ;
            par->cpu->state    = vp_cpu_on;
            del (par->cpu) ;
            del (par->node);
            del (par->root);
}

