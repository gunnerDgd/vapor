#ifndef __CORE_KVM_MAP_MMIO_H__
#define __CORE_KVM_MAP_MMIO_H__

#include "../map.h"

typedef struct vp_mmio_ops                    {
    bool_t (*rd8)  (obj*, void*, u8_t*)       ;
    bool_t (*rd16) (obj*, void*, u16_t*)      ;
    bool_t (*rd32) (obj*, void*, u32_t*)      ;
    bool_t (*rd64) (obj*, void*, u64_t*)      ;
    bool_t (*read) (obj*, void*, void*, u64_t);

    bool_t (*wr8)  (obj*, void*, u8_t *)      ;
    bool_t (*wr16) (obj*, void*, u16_t*)      ;
    bool_t (*wr32) (obj*, void*, u32_t*)      ;
    bool_t (*wr64) (obj*, void*, u64_t*)      ;
    bool_t (*write)(obj*, void*, void*, u64_t);
}   vp_mmio_ops;

bool_t vp_mmio_map  (vp_map*, vp_mmio_ops*, obj*) ;
bool_t vp_mmio_rd8  (vp_map*, void*, u8_t *)      ;
bool_t vp_mmio_rd16 (vp_map*, void*, u16_t*)      ;
bool_t vp_mmio_rd32 (vp_map*, void*, u32_t*)      ;
bool_t vp_mmio_rd64 (vp_map*, void*, u64_t*)      ;
bool_t vp_mmio_read (vp_map*, void*, void*, u64_t);

bool_t vp_mmio_wr8  (vp_map*, void*, u8_t *)      ;
bool_t vp_mmio_wr16 (vp_map*, void*, u16_t*)      ;
bool_t vp_mmio_wr32 (vp_map*, void*, u32_t*)      ;
bool_t vp_mmio_wr64 (vp_map*, void*, u64_t*)      ;
bool_t vp_mmio_write(vp_map*, void*, void*, u64_t);

#endif