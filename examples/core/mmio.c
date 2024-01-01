#include <vp/vp.h>

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>

bool_t mmio_rd8  (obj* par, void* addr, u8_t * buf)            { printf("MMIO INPUT (1) : %08x\n", addr); *buf = 5; return true_t; }
bool_t mmio_rd16 (obj* par, void* addr, u16_t* buf)            { printf("MMIO INPUT (2) : %08x\n", addr); *buf = 5; return true_t; }
bool_t mmio_rd32 (obj* par, void* addr, u32_t* buf)            { printf("MMIO INPUT (4) : %08x\n", addr); *buf = 5; return true_t; }
bool_t mmio_rd64 (obj* par, void* addr, u64_t* buf)            { printf("MMIO INPUT (8) : %08x\n", addr); *buf = 5; return true_t; }
bool_t mmio_read (obj* par, void* addr, void * buf, u64_t len) {                                                    return true_t; }

bool_t mmio_wr8  (obj* par, void* addr, u8_t * buf)            { printf("MMIO OUTPUT (1) : %d\n", *buf); return true_t; }
bool_t mmio_wr16 (obj* par, void* addr, u16_t* buf)            { printf("MMIO OUTPUT (2) : %d\n", *buf); return true_t; }
bool_t mmio_wr32 (obj* par, void* addr, u32_t* buf)            { printf("MMIO OUTPUT (4) : %d\n", *buf); return true_t; }
bool_t mmio_wr64 (obj* par, void* addr, u64_t* buf)            { printf("MMIO OUTPUT (8) : %d\n", *buf); return true_t; }
bool_t mmio_write(obj* par, void* addr, void * buf, u64_t len) {                                         return true_t; }

typedef struct mmio_dev {
    obj head;
}   mmio_dev;

vp_mmio_ops mmio_ops = {
    .rd8   = mmio_rd8  ,
    .rd16  = mmio_rd16 ,
    .rd32  = mmio_rd32 ,
    .rd64  = mmio_rd64 ,
    .read  = mmio_read ,

    .wr8   = mmio_wr8  ,
    .wr16  = mmio_wr16 ,
    .wr32  = mmio_wr32 ,
    .wr64  = mmio_wr64 ,
    .write = mmio_write
};

obj_trait mmio_dev_t         = {
    .on_new   = 0             ,
    .on_clone = 0             ,
    .on_ref   = 0             ,
    .on_del   = 0             ,
    .size     = sizeof(mmio_dev)
};

vp_main()                                                                                                                      {
    vp_sys    sys  = make (vp_sys_t)    from (0)             ; if (!sys)  { printf("Failed to Create VM System\n"); return -1; }
    vp_cpu    cpu  = make (vp_cpu_t)    from (1, sys)        ; if (!cpu)  { printf("Failed to Create VCPU\n")     ; return -1; }
    mmio_dev* mmio = make (&mmio_dev_t) from (0)             ; if (!mmio) { printf("Failed to Create PIO\n")      ; return -1; }

    vp_map    map0 = make (vp_map_t)    from (2, 0 kb, 4  kb);
    vp_map    map1 = make (vp_map_t)    from (2, 8 kb, 12 kb);

    int       mmap0_file = open ("core-mmio-asm", O_RDWR);
    void     *mmap0      = mmap (0, 4 kb, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (!map0)                               { printf("Failed to Create Map"); return -1; }
    if (!vp_mem_map (map0, mmap0    , 4 kb)) { printf("Failed to Map Memory"); return -1; }
    if (!vp_mmio_map(map1, &mmio_ops, mmio)) { printf("Failed to Map Memory"); return -1; }

    if (!vp_mmu_map(vp_sys_mmu(sys), map0))  { printf("Failed to Map Memory to MMU"); return -1; }
    if (!vp_mmu_map(vp_sys_mmu(sys), map1))  { printf("Failed to Map Memory to MMU"); return -1; }

    vp_reg cpu_reg  = make (vp_reg_t)  from (1, cpu);
    vp_reg cpu_sreg = make (vp_sreg_t) from (1, cpu);
    if   (!cpu_reg)  { printf("Failed to Fetch Register"); return -1; }
    if   (!cpu_sreg) { printf("Failed to Fetch Register"); return -1; }

    vp_reg_set(cpu_reg, vp_rip   , 0)   ;
    vp_reg_set(cpu_reg, vp_rax   , 4)   ;
    vp_reg_set(cpu_reg, vp_rbx   , 8 kb);
    vp_reg_set(cpu_reg, vp_rflags, 2)   ;

    u64_t base     = 0ull; vp_seg_base(cpu_sreg, vp_cs, &base)    ;
    u64_t selector = 0ull; vp_seg_base(cpu_sreg, vp_cs, &selector);

    del(cpu_reg) ;
    del(cpu_sreg);

    vp_run  run      = make (vp_run_t)  from (1, cpu); if (!run)      { printf("Failed to Run vCPU"); return -1; }
    vp_mmio run_mmio = make (vp_mmio_t) from (1, run); if (!run_mmio) { printf("Failed to Run vCPU"); return -1; }
    del    (run_mmio);
    del    (run)     ;

    run      = make (vp_run_t)  from (1, cpu); if (!run)      { printf("Failed to Run vCPU"); return -1; }
    run_mmio = make (vp_mmio_t) from (1, run); if (!run_mmio) { printf("Failed to Run vCPU"); return -1; }
    del    (run_mmio);
    del    (run)     ;
}