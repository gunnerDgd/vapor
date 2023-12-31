#ifndef __VP_CORE_MAP_PIO_H__
#define __VP_CORE_MAP_PIO_H__

#include "../map.h"

typedef struct vp_pio_ops                {
    bool_t (*map)  (obj*, vp_map)        ;
    bool_t (*unmap)(obj*, vp_map)        ;

    bool_t (*rd8)  (obj*, u16_t, u8_t *) ;
    bool_t (*rd16) (obj*, u16_t, u16_t*) ;
    bool_t (*rd32) (obj*, u16_t, u32_t*) ;

    bool_t (*wr8)  (obj*, u16_t, u8_t *) ;
    bool_t (*wr16) (obj*, u16_t, u16_t*) ;
    bool_t (*wr32) (obj*, u16_t, u32_t*) ;
}   vp_pio_ops;

bool_t vp_pio_map (vp_map, vp_pio_ops *, obj*);
bool_t vp_pio_rd8 (vp_map, u16_t, u8_t *)     ;
bool_t vp_pio_rd16(vp_map, u16_t, u16_t*)     ;
bool_t vp_pio_rd32(vp_map, u16_t, u32_t*)     ;

bool_t vp_pio_wr8 (vp_map, u16_t, u8_t *)     ;
bool_t vp_pio_wr16(vp_map, u16_t, u16_t*)     ;
bool_t vp_pio_wr32(vp_map, u16_t, u32_t*)     ;

#endif