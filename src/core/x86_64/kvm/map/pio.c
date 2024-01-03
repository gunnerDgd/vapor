#include "pio.h"
#include "../map.h"

bool_t
    vp_pio_map
        (vp_map* par, vp_pio_ops* par_ops, obj* par_pio) {
            if (!par)                      return false_t;
            if (!par_ops)                  return false_t;
            if (!par_pio)                  return false_t;
            if (trait_of(par) != vp_map_t) return false_t;

            if (!vp_map_none(par))         return false_t;
            if (!par_ops->rd8)             return false_t;
            if (!par_ops->rd16)            return false_t;
            if (!par_ops->rd32)            return false_t;

            if (!par_ops->wr8)             return false_t;
            if (!par_ops->wr16)            return false_t;
            if (!par_ops->wr32)            return false_t;

            par->map_ops.pio = par_ops;
            par->map         = par_pio;

            return true_t;
}

bool_t
    vp_pio_rd8
        (vp_map* par, u16_t par_pio, u8_t* par_buf)      {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map_ops.pio)         return false_t;
            if (!par->map)                 return false_t;

            return par->map_ops.pio->rd8 (
                   par->map_ops.pio,
                   par_pio         ,
                   par_buf
            );
}

bool_t
    vp_pio_rd16
        (vp_map* par, u16_t par_pio, u16_t* par_buf)     {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map)                 return false_t;
            if (!par->map_ops.pio)         return false_t;

            return par->map_ops.pio->rd16 (
                   par->map_ops.pio,
                   par_pio         ,
                   par_buf
            );
}

bool_t
    vp_pio_rd32
        (vp_map* par, u16_t par_pio, u32_t* par_buf)     {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map)                 return false_t;
            if (!par->map_ops.pio)         return false_t;

            return par->map_ops.pio->rd32 (
                   par->map_ops.pio,
                   par_pio         ,
                   par_buf
            );
}

bool_t
    vp_pio_wr8
        (vp_map* par, u16_t par_pio, u8_t* par_buf)      {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map)                 return false_t;
            if (!par->map_ops.pio)         return false_t;

            return par->map_ops.pio->wr8 (
                   par->map_ops.pio,
                   par_pio         ,
                   par_buf
            );
}

bool_t
    vp_pio_wr16
        (vp_map* par, u16_t par_pio, u16_t* par_buf)     {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map)                 return false_t;
            if (!par->map_ops.pio)         return false_t;

            return par->map_ops.pio->wr16 (
                   par->map_ops.pio,
                   par_pio         ,
                   par_buf
            );
}

bool_t
    vp_pio_wr32
        (vp_map* par, u16_t par_pio, u32_t* par_buf)     {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map)                 return false_t;
            if (!par->map_ops.pio)         return false_t;

            return par->map_ops.pio->wr32 (
                   par->map_ops.pio,
                   par_pio         ,
                   par_buf
            );
}