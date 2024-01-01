#include <vp/vp.h>

#include <stdio.h>
#include <sys/mman.h>

bool_t pio_rd8 (obj* par, u16_t port, u8_t * buf) { *buf = 8; return true_t; }
bool_t pio_rd16(obj* par, u16_t port, u16_t* buf) { *buf = 8; return true_t; }
bool_t pio_rd32(obj* par, u16_t port, u32_t* buf) { *buf = 8; return true_t; }

bool_t pio_wr8 (obj* par, u16_t port, u8_t * buf) { printf("PIO OUTPUT (1) : %d\n", *buf); return true_t; }
bool_t pio_wr16(obj* par, u16_t port, u16_t* buf) { printf("PIO OUTPUT (2) : %d\n", *buf); return true_t;  }
bool_t pio_wr32(obj* par, u16_t port, u32_t* buf) { printf("PIO OUTPUT (4) : %d\n", *buf); return true_t;  }

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

vp_pio_ops pio_ops = {
    .rd8  = pio_rd8 ,
    .rd16 = pio_rd16,
    .rd32 = pio_rd32,
    .wr8  = pio_wr8 ,
    .wr16 = pio_wr16,
    .wr32 = pio_wr32
};

obj_trait pio_dev_t         = {
    .on_new   = 0             ,
    .on_clone = 0             ,
    .on_ref   = 0             ,
    .on_del   = 0             ,
    .size     = sizeof(pio_dev)
};

vp_main()                                                                                                          {
    vp_sys   sys = make (vp_sys_t)   from (0)     ; if (!sys) { printf("Failed to Create VM System\n"); return -1; }
    vp_cpu   cpu = make (vp_cpu_t)   from (1, sys); if (!cpu) { printf("Failed to Create VCPU\n")     ; return -1; }
    pio_dev* pio = make (&pio_dev_t) from (0)     ; if (!pio) { printf("Failed to Create PIO\n")      ; return -1; }

    vp_map   map0  = make (vp_map_t) from (2, 4 kb, 8 kb)  ;
    vp_map   map1  = make (vp_map_t) from (2, 0x3f8, 0x3f9);
    void    *mmap0 = mmap (0, 4 kb, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    mem_copy(mmap0, mmap0_code, sizeof(mmap0_code));

    if (!map0)                              { printf("Failed to Create Map"); return -1; }
    if (!vp_mem_map(map0, mmap0, 4 kb))     { printf("Failed to Map Memory"); return -1; }
    if (!vp_pio_map(map1, &pio_ops, pio))   { printf("Failed to Map Memory"); return -1; }

    if (!vp_mmu_map(vp_sys_mmu(sys), map0)) { printf("Failed to Map Memory"); return -1; }
    if (!vp_mmu_map(vp_sys_mmu(sys), map1)) { printf("Failed to Map Memory"); return -1; }

    vp_reg cpu_reg  = make (vp_reg_t)  from (1, cpu);
    vp_reg cpu_sreg = make (vp_sreg_t) from (1, cpu);
    if   (!cpu_reg)  { printf("Failed to Fetch Register"); return -1; }
    if   (!cpu_sreg) { printf("Failed to Fetch Register"); return -1; }

    vp_reg_set(cpu_reg, vp_rip   , 4 kb);
    vp_reg_set(cpu_reg, vp_rax   , 3)   ;
    vp_reg_set(cpu_reg, vp_rbx   , 4)   ;
    vp_reg_set(cpu_reg, vp_rflags, 2)   ;

    u64_t base     = 0ull; vp_seg_base(cpu_sreg, vp_cs, &base)    ;
    u64_t selector = 0ull; vp_seg_base(cpu_sreg, vp_cs, &selector);

    del(cpu_reg) ;
    del(cpu_sreg);

    vp_run run = make (vp_run_t) from (1, cpu);
    if (!run) { printf("Failed to Run vCPU"); return -1; }

    vp_pio run_pio = make (vp_pio_t) from (1, run);
    del   (run_pio);
}