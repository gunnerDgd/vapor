#ifndef __VP_CORE_MAP_MMIO_H__
#define __VP_CORE_MAP_MMIO_H__

#include <obj.h>

typedef struct vp_mmio_ops                    {
    bool_t (*map)  (obj*, struct vp_map*)     ;
    bool_t (*unmap)(obj*, struct vp_map*)     ;

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

bool_t vp_mmio_map  (struct vp_map*, vp_mmio_ops*, obj*) ;
bool_t vp_mmio_rd8  (struct vp_map*, void*, u8_t *)      ;
bool_t vp_mmio_rd16 (struct vp_map*, void*, u16_t*)      ;
bool_t vp_mmio_rd32 (struct vp_map*, void*, u32_t*)      ;
bool_t vp_mmio_rd64 (struct vp_map*, void*, u64_t*)      ;
bool_t vp_mmio_read (struct vp_map*, void*, void*, u64_t);

bool_t vp_mmio_wr8  (struct vp_map*, void*, u8_t *)      ;
bool_t vp_mmio_wr16 (struct vp_map*, void*, u16_t*)      ;
bool_t vp_mmio_wr32 (struct vp_map*, void*, u32_t*)      ;
bool_t vp_mmio_wr64 (struct vp_map*, void*, u64_t*)      ;
bool_t vp_mmio_write(struct vp_map*, void*, void*, u64_t);
#endif