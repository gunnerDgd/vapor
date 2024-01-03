#include "mmio.h"

#include "../cpu.h"
#include "../node.h"

#include "../root.h"
#include "../../root.h"

#include "../map.h"
#include "../../map.h"

obj_trait vp_mmio_trait     = {
    .on_new   = &vp_mmio_new  ,
    .on_clone = &vp_mmio_clone,
    .on_ref   = 0             ,
    .on_del   = &vp_mmio_del  ,
    .size     = sizeof(vp_mmio)
};

obj_trait *vp_mmio_t = &vp_mmio_trait;

bool_t
    vp_mmio_new
        (vp_mmio* par_mmio, u32_t par_count, va_list par) {
            vp_cpu* cpu = va_arg(par, vp_cpu*);
            if (!cpu)                                                  return false_t;
            if (trait_of(cpu) != vp_cpu_t)                             return false_t;
            if (cpu->run.ExitReason != WHvRunVpExitReasonMemoryAccess) return false_t;

            vp_node *node = cpu->node; if (!node) return false_t;
            vp_root *root = cpu->root; if (!root) return false_t;

            if (trait_of(node) != vp_node_t) return false_t;
            if (trait_of(root) != vp_root_t) return false_t;
            
            par_mmio->cpu  = ref(cpu) ;
            par_mmio->node = ref(node);
            par_mmio->root = ref(root);

            par_mmio->dir  = cpu->run.MemoryAccess.AccessInfo.AccessType;
            par_mmio->addr = cpu->run.MemoryAccess.Gpa                  ;
            par_mmio->size = cpu->run.MemoryAccess.InstructionByteCount ;
            par_mmio->data = cpu->run.MemoryAccess.InstructionBytes     ;

            return true_t;
}

bool_t
    vp_mmio_clone
        (vp_mmio* par, vp_mmio* par_clone) {
            return false_t;
}

void
    vp_mmio_del
        (vp_mmio* par)                                            {
            WHV_EMULATOR_STATUS res_state                         ;
            HRESULT             res = WHvEmulatorTryMmioEmulation (
                par->cpu->emu             ,
                par                       ,
               &par->cpu->run.VpContext   ,
               &par->cpu->run.MemoryAccess,
               &res_state
            );
        
            par->cpu->run_task = 0        ;
            par->cpu->state    = vp_cpu_on;
            del(par->cpu) ;
            del(par->root);
            del(par->node);
}