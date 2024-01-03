#include <vp/vp.h>

#include <Windows.h>
#include <stdio.h>

vp_main() {
    vp_root root     = make(vp_root_t) from(1, 4);
    vp_map  map0     = vp_root_map(root, 0, 4 kb);
    void   *map0_mem = VirtualAlloc(0, 4 kb, MEM_COMMIT, PAGE_READWRITE);

    map0 = vp_map_mem(map0, map0_mem);
    printf("Hello VM !!\n");
}