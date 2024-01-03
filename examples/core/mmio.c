#include <vp/vp.h>

#include <stdio.h>
#include <Windows.h>

bool_t mmio_map  (obj* par, vp_map par_map) { printf("MMIO Mapped\n")  ; return true_t; }
bool_t mmio_unmap(obj* par)                 { printf("MMIO Unmapped\n"); return true_t; }

bool_t mmio_read (obj* par, void* port, u8_t* buf, u64_t len) { printf("MMIO INPUT : %d\n", len)      ;* buf = 5; return true_t; }
bool_t mmio_write(obj* par, void* port, u8_t* buf, u64_t len) { printf("MMIO OUTPUT (1) : %d\n", *buf);           return true_t; }

const u8_t mmap0_code[] = { 0x8A, 0x03, 0x04, 0x01, 0x88, 0x03, 0xF4 };

typedef struct mmio_dev {
    obj head;
}   mmio_dev;

vp_map_ops map_ops   = {
    .map   = mmio_map  ,
    .unmap = mmio_unmap,
    .read  = mmio_read ,
    .write = mmio_write
};

obj_trait mmio_dev_t         = {
    .on_new   = 0              ,
    .on_clone = 0              ,
    .on_ref   = 0              ,
    .on_del   = 0              ,
    .size     = sizeof(mmio_dev)
};

vp_main()                                           {
    vp_root root  = make(vp_root_t) from(1, 4)      ;
    vp_node node0 = vp_root_node(root , 0)          ;
    vp_cpu  cpu0  = vp_node_cpu (node0, 0)          ;
    vp_map  map0  = vp_root_map (root, 4  kb, 8  kb);
    vp_map  map1  = vp_root_map (root, 12 kb, 16 kb);
    vp_map  map2  = vp_root_map (root, 0  kb, 4  kb);

    void *map0_mem = VirtualAlloc(0, 4 kb, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    map0 = vp_map_mem (map0, map0_mem);
    map1 = vp_map_mmio(map1, &map_ops, make (&mmio_dev_t) from (0));
    map2 = vp_map_mmio(map2, &map_ops, make (&mmio_dev_t) from (0));
    mem_copy(map0_mem, mmap0_code, sizeof(mmap0_code));

    vp_reg cpu_reg  = make (vp_reg_t)  from (1, cpu0);
    vp_reg cpu_sreg = make (vp_sreg_t) from (1, cpu0);

    vp_reg_set(cpu_reg, vp_rip   , 4  kb);
    vp_reg_set(cpu_reg, vp_rdi   , 12 kb);
    vp_reg_set(cpu_reg, vp_rflags, 2)    ;

    u64_t base     = 0ull; vp_seg_base(cpu_sreg, vp_cs, &base)    ;
    u64_t selector = 0ull; vp_seg_base(cpu_sreg, vp_cs, &selector);

    del(cpu_reg) ;
    del(cpu_sreg);

    obj* run = vp_cpu_run(cpu0); del(run);
    run = vp_cpu_run(cpu0); del(run);
    run = vp_cpu_run(cpu0); del(run);
}