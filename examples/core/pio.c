#include <vp/vp.h>

#include <stdio.h>
#include <Windows.h>

bool_t pio_map  (obj* par, vp_map par_map) { printf("PIO Mapped\n")  ; return true_t; }
bool_t pio_unmap(obj* par)                 { printf("PIO Unmapped\n"); return true_t; }

bool_t pio_read (obj* par, void* port, u8_t* buf, u64_t len) { *buf = 8;                              return true_t; }
bool_t pio_write(obj* par, void* port, u8_t* buf, u64_t len) { printf("PIO OUTPUT (1) : %d\n", *buf); return true_t; }

const u8_t mmap0_code[] = {
        0xba, 0xf8, 0x03, /* mov $0x3f8, %dx */
        0x00, 0xd8,       /* add %bl, %al */
        0xee,             /* out %al, (%dx) */
        0xb0, '\n',       /* mov $'\n', %al */
        0xee,             /* out %al, (%dx) */
        0xf4,             /* hlt */
};

typedef struct pio_dev {
    obj head;
}   pio_dev;

vp_map_ops map_ops  = {
    .map   = pio_map  ,
    .unmap = pio_unmap,
    .read  = pio_read ,
    .write = pio_write
};

obj_trait pio_dev_t         = {
    .on_new   = 0             ,
    .on_clone = 0             ,
    .on_ref   = 0             ,
    .on_del   = 0             ,
    .size     = sizeof(pio_dev)
};

vp_main()                                              {
    vp_root root     = make(vp_root_t) from(1, 4)      ;
    vp_node node0    = vp_root_node(root , 0)          ;
    vp_cpu  cpu0     = vp_node_cpu (node0, 0)          ;
    vp_map  map0     = vp_root_map (root, 4  kb, 8 kb) ;
    vp_map  map1     = vp_port_map (root, 0x3f8, 0x3f9);

    void   *map0_mem = VirtualAlloc(0, 4 kb, MEM_COMMIT, PAGE_READWRITE);
    map0 = vp_map_mem(map0, map0_mem);
    map1 = vp_map_pio(map1, &map_ops, make (&pio_dev_t) from (0));
    mem_copy(map0_mem, mmap0_code, sizeof(mmap0_code));

    vp_reg cpu_reg  = make (vp_reg_t)  from (1, cpu0);
    vp_reg cpu_sreg = make (vp_sreg_t) from (1, cpu0);

    vp_reg_set(cpu_reg, vp_rip   , 4 kb);
    vp_reg_set(cpu_reg, vp_rax   , 3)   ;
    vp_reg_set(cpu_reg, vp_rbx   , 4)   ;
    vp_reg_set(cpu_reg, vp_rflags, 2)   ;

    u64_t base     = 0ull; vp_seg_base(cpu_sreg, vp_cs, &base)    ;
    u64_t selector = 0ull; vp_seg_base(cpu_sreg, vp_cs, &selector);

    del(cpu_reg) ;
    del(cpu_sreg);

    obj* run = vp_cpu_run(cpu0);
    del (run);
}