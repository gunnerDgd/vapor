#include "cpu.h"

#include "root.h"
#include "../root.h"

#include "node.h"

#include "run/pio.h"
#include "run/mmio.h"

#include "map.h"
#include "../map.h"

i32_t
    vp_cpu_do_pio
        (obj* par, WHV_EMULATOR_IO_ACCESS_INFO* par_pio) {
            if (!par)                      return -1;
            if (!par_pio)                  return -1;
            if (trait_of(par) != vp_pio_t) return -1; vp_pio* pio = par;

            u64_t dir  =  par_pio->Direction              ;
            void* data = &par_pio->Data                   ;
            u64_t addr =  par_pio->Port                   ; if (addr > 0xFFFF) return -1;
            u64_t size =  par_pio->AccessSize             ; if (size > 4)      return -1;
            void* port =  vp_port_find(pio->root, addr, 1); if (!port)         return -1;

            if (dir == vp_pio_in)  vp_map_read (port, addr, data, size);
            if (dir == vp_pio_out) vp_map_write(port, addr, data, size);

            return S_OK;
}

i32_t
    vp_cpu_do_mmio
        (obj* par, WHV_EMULATOR_MEMORY_ACCESS_INFO* par_mmio) {
            if (!par)                       return -1;
            if (!par_mmio)                  return -1;
            if (trait_of(par) != vp_mmio_t) return -1; vp_mmio* mmio = par;

            u64_t dir  = par_mmio->Direction                     ;
            void *data = par_mmio->Data                          ;
            u64_t addr = par_mmio->GpaAddress                    ;
            u64_t size = par_mmio->AccessSize                    ; 
            void* map  = vp_root_map_find(mmio->root, addr, size); if (!map) return -1;

            if (dir == vp_mmio_in)  vp_map_read (map, addr, data, size);
            if (dir == vp_mmio_out) vp_map_write(map, addr, data, size);

            return S_OK;
}

i32_t
    vp_cpu_do_translate
        (obj* par, u64_t par_gva, u64_t par_flag, u64_t* par_res, u64_t* par_gpa) {
            if      (!par)                       return -1                 ; vp_cpu* cpu = 0;
            if      (trait_of(par) == vp_cpu_t)  cpu = par                 ;
            else if (trait_of(par) == vp_mmio_t) cpu = ((vp_mmio*)par)->cpu;
            else if (trait_of(par) == vp_pio_t)  cpu = ((vp_pio*) par)->cpu;
            else                                 return -1;

            vp_root* root = cpu->root;
            if (!cpu)  return -1;
            if (!root) return -1;

            if (trait_of(cpu)  != vp_cpu_t)  return -1;
            if (trait_of(root) != vp_root_t) return -1;

            return WHvTranslateGva (
                root->root,
                cpu->cpu  ,
                par_gva   ,
                par_flag  ,
                par_res   ,
                par_gpa
            );
}

i32_t
    vp_cpu_do_sync_in
        (obj* par, void* par_reg, u64_t par_count, void* par_val) {
            if (!par)     return -1;
            if (!par_reg) return -1;
            if (!par_val) return -1;

            vp_cpu* cpu = 0;
            if (trait_of(par) == vp_cpu_t)  cpu = par                 ;
            if (trait_of(par) == vp_pio_t)  cpu = ((vp_pio*) par)->cpu;
            if (trait_of(par) == vp_mmio_t) cpu = ((vp_mmio*)par)->cpu;
            if (!cpu)                       return -1                 ;

            vp_root* root = cpu->root;
            if (!root)                       return -1;
            if (trait_of(root) != vp_root_t) return -1;

            return WHvGetVirtualProcessorRegisters (
                root->root,
                cpu ->cpu ,
                par_reg   ,
                par_count ,
                par_val
            );
}

i32_t
    vp_cpu_do_sync_out
        (obj* par, void* par_reg, u64_t par_count, void* par_val) {
            if (!par)     return -1;
            if (!par_reg) return -1;
            if (!par_val) return -1;

            vp_cpu* cpu = 0;
            if (trait_of(par) == vp_cpu_t)  cpu = par                 ;
            if (trait_of(par) == vp_pio_t)  cpu = ((vp_pio*) par)->cpu;
            if (trait_of(par) == vp_mmio_t) cpu = ((vp_mmio*)par)->cpu;
            if (!cpu)                       return -1                 ;

            vp_root* root = cpu->root;
            if (!root)                       return -1;
            if (trait_of(root) != vp_root_t) return -1;

            return WHvSetVirtualProcessorRegisters (
                root->root,
                cpu ->cpu ,
                par_reg   ,
                par_count ,
                par_val
            );
}

WHV_EMULATOR_CALLBACKS vp_cpu_do             =                               {
    .Size                                    = sizeof(WHV_EMULATOR_CALLBACKS),
    .WHvEmulatorIoPortCallback               = &vp_cpu_do_pio                ,
    .WHvEmulatorMemoryCallback               = &vp_cpu_do_mmio               ,
    .WHvEmulatorGetVirtualProcessorRegisters = &vp_cpu_do_sync_in            ,
    .WHvEmulatorSetVirtualProcessorRegisters = &vp_cpu_do_sync_out           ,
    .WHvEmulatorTranslateGvaPage             = &vp_cpu_do_translate
};

obj_trait vp_cpu_trait     = {
    .on_new   = &vp_cpu_new  ,
    .on_clone = &vp_cpu_clone,
    .on_ref   = 0            ,
    .on_del   = &vp_cpu_del  ,
    .size     = sizeof(vp_cpu)
};

obj_trait* vp_cpu_t = &vp_cpu_trait;

bool_t
    vp_cpu_new
        (vp_cpu* par_cpu, u32_t par_count, va_list par) {
            par_cpu->root = va_arg(par, vp_root*);
            par_cpu->node = va_arg(par, vp_node*);
            par_cpu->cpu  = va_arg(par, u64_t)   ;

            if (par_count != 3) return false_t;
            if (!par_cpu->root) return false_t;
            if (!par_cpu->node) return false_t;

            if (trait_of(par_cpu->root) != vp_root_t)                                     return false_t;
            if (trait_of(par_cpu->node) != vp_node_t)                                     return false_t;
            if (WHvEmulatorCreateEmulator (&vp_cpu_do, &par_cpu->emu, 0)         != S_OK) return false_t;
            if (WHvCreateVirtualProcessor (par_cpu->root->root, par_cpu->cpu, 0) != S_OK) {
                WHvEmulatorDestroyEmulator(par_cpu->emu);
                return false_t;
            }

            par_cpu->run_task = 0                 ; mem_set(&par_cpu->run, 0x00, sizeof(par_cpu->run));
            par_cpu->root     = ref(par_cpu->root);
            par_cpu->node     = ref(par_cpu->node);
            return true_t;
}

bool_t
    vp_cpu_clone
        (vp_cpu* par, vp_cpu* par_clone) {
            return false_t;
}

void
    vp_cpu_del
        (vp_cpu* par)                                            {
            WHvDeleteVirtualProcessor (par->root->root, par->cpu);
            WHvEmulatorDestroyEmulator(par->emu)                 ;
            del(par->root);
            del(par->node);
}