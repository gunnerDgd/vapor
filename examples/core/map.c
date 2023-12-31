#include <vp/vp.h>
#include <stdio.h>

vp_main()                                                 {
    vp_sys sys      = make (vp_sys_t) from (0)            ; if (!sys)      { printf("Failed to Create VM System\n"); return -1; }
    vp_cpu cpu      = make (vp_cpu_t) from (1, sys)       ; if (!cpu)      { printf("Failed to Create VCPU\n")     ; return -1; }
    vp_map map      = make (vp_map_t) from (2, 0   , 1 mb); if (!map)      { printf("Failed to Create VM Memory Map (%08x - %08x)\n", vp_map_begin(map)     , vp_map_end(map))     ; return -1; }
    vp_map map_sub1 = make (vp_map_t) from (2, 0   , 1 kb); if (!map_sub1) { printf("Failed to Create VM Memory Map (%08x - %08x)\n", vp_map_begin(map_sub1), vp_map_end(map_sub1)); return -1; }
    vp_map map_sub2 = make (vp_map_t) from (2, 1 kb, 2 kb); if (!map_sub2) { printf("Failed to Create VM Memory Map (%08x - %08x)\n", vp_map_begin(map_sub2), vp_map_end(map_sub2)); return -1; }
    vp_map map_sub3 = make (vp_map_t) from (2, 2 kb, 3 kb); if (!map_sub3) { printf("Failed to Create VM Memory Map (%08x - %08x)\n", vp_map_begin(map_sub3), vp_map_end(map_sub3)); return -1; }
    vp_map map_sub4 = make (vp_map_t) from (2, 1 kb, 3 kb); if (!map_sub4) { printf("Failed to Create VM Memory Map (%08x - %08x)\n", vp_map_begin(map_sub4), vp_map_end(map_sub4)); return -1; }

    map      = vp_mmu_map(vp_sys_mmu(sys), map)     ; if(!map)      { printf("Failed to Map Region (%08x - %08x)\n", vp_map_begin(map), vp_map_end(map)); return -1; }
    map_sub1 = vp_mmu_map(vp_sys_mmu(sys), map_sub1); if(!map_sub1) { printf("Failed to Map Region (%08x - %08x)\n", vp_map_begin(map), vp_map_end(map)); return -1; }
    map_sub2 = vp_mmu_map(vp_sys_mmu(sys), map_sub2); if(!map_sub2) { printf("Failed to Map Region (%08x - %08x)\n", vp_map_begin(map), vp_map_end(map)); return -1; }
    map_sub3 = vp_mmu_map(vp_sys_mmu(sys), map_sub3); if(!map_sub3) { printf("Failed to Map Region (%08x - %08x)\n", vp_map_begin(map), vp_map_end(map)); return -1; }
    map_sub4 = vp_mmu_map(vp_sys_mmu(sys), map_sub4); if (map_sub4) { printf("Illegal Mapping (%08x - %08x)\n"     , vp_map_begin(map), vp_map_end(map)); return -1; }

    printf("Hello VM !!\n");
}