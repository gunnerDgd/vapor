#include <vp/vp.h>
#include <stdio.h>

vp_main()                                         {
    vp_sys sys = make (vp_sys_t) from (0)         ; if (!sys) { printf("Failed to Create VM System\n")    ; return -1; }
    vp_cpu cpu = make (vp_cpu_t) from (1, sys)    ; if (!cpu) { printf("Failed to Create VCPU\n")         ; return -1; }
    vp_map map = make (vp_map_t) from (2, 0, 1 mb); if (!map) { printf("Failed to Create VM Memory Map\n"); return -1; }
    map = vp_mmu_map(vp_sys_mmu(sys), map)        ; if (!map) { printf("Failed to Map Memory Region\n")   ; return -1; }

    printf ("Hello VM !!\n");
}