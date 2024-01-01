#include <vp/vp.h>
#include <stdio.h>

#include <sys/mman.h>

vp_main()                                     {
    vp_sys sys = make (vp_sys_t) from (0)     ;
    vp_cpu cpu = make (vp_cpu_t) from (1, sys);

    if (!sys) { printf("Failed to Create VM System\n"); return -1; }
    if (!cpu) { printf("Failed to Create VCPU\n")     ; return -1; }

    vp_map map0 = make (vp_map_t) from (2, 4  kb, 8  kb);
    vp_map map1 = make (vp_map_t) from (2, 8  kb, 12 kb);
    vp_map map2 = make (vp_map_t) from (2, 12 kb, 16 kb);

    void* mmap0 = mmap(0, 4 kb, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    void* mmap1 = mmap(0, 4 kb, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    void* mmap2 = mmap(0, 4 kb, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    vp_mem_map(map0, mmap0, 4 kb); map0 = vp_mmu_map(vp_sys_mmu(sys), map0);
    vp_mem_map(map1, mmap1, 4 kb); map1 = vp_mmu_map(vp_sys_mmu(sys), map1);
    vp_mem_map(map2, mmap2, 4 kb); map2 = vp_mmu_map(vp_sys_mmu(sys), map2);

    if (!map0) { printf("Failed Map (%08x - %08x)\n", vp_map_begin(map0), vp_map_end(map0)); return -1; }
    if (!map1) { printf("Failed Map (%08x - %08x)\n", vp_map_begin(map1), vp_map_end(map1)); return -1; }
    if (!map2) { printf("Failed Map (%08x - %08x)\n", vp_map_begin(map2), vp_map_end(map2)); return -1; }

    vp_map map_find1 = vp_mmu_find(vp_sys_mmu(sys), 5  kb, 1)   ;
    vp_map map_find2 = vp_mmu_find(vp_sys_mmu(sys), 9  kb, 1)   ;
    vp_map map_find3 = vp_mmu_find(vp_sys_mmu(sys), 13 kb, 2 kb);

    printf("Hello VM !!\n");
}