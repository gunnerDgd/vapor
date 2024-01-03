#include "cpu.h"

#include "root.h"
#include "details/root.h"

#include "node.h"
#include "details/node.h"

#include "run/mmio.h"
#include "run/pio.h"
#include "run/halt.h"

obj* 
    vp_cpu_run
        (void* par)                                                             {
            if (!par)                      return 0; vp_cpu* cpu = list_get(par);
            if (!cpu)                      return 0;
            if (trait_of(cpu) != vp_cpu_t) return 0;
            if (cpu->run_task)             return 0;
            if (cpu->state != vp_cpu_on)   return 0;

            vp_root* root = cpu->root; if (!root) return false_t;
            vp_node* node = cpu->node; if (!node) return false_t;

            if (trait_of(root) != vp_root_t) return false_t;
            if (trait_of(node) != vp_node_t) return false_t;
                        
            HRESULT  res  = WHvRunVirtualProcessor (
                root->root     ,
                cpu ->cpu      ,
                &cpu->run      ,
                sizeof(cpu->run)
            );

            if (res != S_OK) return 0;
            switch (cpu->run.ExitReason)              {
                case WHvRunVpExitReasonMemoryAccess   : cpu->run_task = make (vp_mmio_t) from (1, cpu); break;
                case WHvRunVpExitReasonX64Halt        : cpu->run_task = make (vp_halt_t) from (1, cpu); break;
                case WHvRunVpExitReasonX64IoPortAccess: cpu->run_task = make (vp_pio_t)  from (1, cpu); break;
                default                               : return 0;
            }

            cpu->state = vp_cpu_exit;
            return cpu->run_task;
}