#include "mmio.h"
#include "../map.h"

bool_t
    vp_mmio_map
        (vp_map* par, vp_mmio_ops* par_ops, obj* par_mmio) {
            if (!par)                      return false_t;
            if (!par_ops)                  return false_t;
            if (!par_mmio)                 return false_t;
            if (trait_of(par) != vp_map_t) return false_t;

            if (!vp_map_none(par))         return false_t;
            if (!par_ops->rd8)             return false_t;
            if (!par_ops->rd16)            return false_t;
            if (!par_ops->rd32)            return false_t;
            if (!par_ops->rd64)            return false_t;
            if (!par_ops->read)            return false_t;

            if (!par_ops->wr8)             return false_t;
            if (!par_ops->wr16)            return false_t;
            if (!par_ops->wr32)            return false_t;
            if (!par_ops->wr64)            return false_t;
            if (!par_ops->write)           return false_t;

            par->map_ops.mmio = par_ops      ;
            par->map          = ref(par_mmio);
            return true_t;
}

bool_t
    vp_mmio_rd8
        (vp_map* par, void* par_mmio, u8_t* par_buf)     {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map_ops.mmio)        return false_t;
            if (!par->map)                 return false_t;

            return par->map_ops.mmio->rd8 (
                par->map_ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_rd16
        (vp_map* par, void* par_mmio, u16_t* par_buf)    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map_ops.mmio)        return false_t;
            if (!par->map)                 return false_t;

            return par->map_ops.mmio->rd16 (
                par->map_ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_rd32
        (vp_map* par, void* par_mmio, u32_t* par_buf)    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map_ops.mmio)        return false_t;
            if (!par->map)                 return false_t;

            return par->map_ops.mmio->rd32 (
                par->map_ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_rd64
        (vp_map* par, void* par_mmio, u64_t* par_buf)    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map_ops.mmio)        return false_t;
            if (!par->map)                 return false_t;

            return par->map_ops.mmio->rd64 (
                par->map_ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_read
        (vp_map* par, void* par_mmio, void* par_buf, u64_t par_len) {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map_ops.mmio)        return false_t;
            if (!par->map)                 return false_t;

            return par->map_ops.mmio->read (
                par->map_ops.mmio,
                par_mmio     ,
                par_buf      ,
                par_len
            );
}

bool_t
    vp_mmio_wr8
        (vp_map* par, void* par_mmio, u8_t* par_buf)     {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map_ops.mmio)        return false_t;
            if (!par->map)                 return false_t;

            return par->map_ops.mmio->wr8 (
                par->map_ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_wr16
        (vp_map* par, void* par_mmio, u16_t* par_buf)    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map_ops.mmio)        return false_t;
            if (!par->map)                 return false_t;

            return par->map_ops.mmio->wr16 (
                par->map_ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_wr32
        (vp_map* par, void* par_mmio, u32_t* par_buf)    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map_ops.mmio)        return false_t;
            if (!par->map)                 return false_t;

            return par->map_ops.mmio->wr32 (
                par->map_ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_wr64
        (vp_map* par, void* par_mmio, u64_t* par_buf)    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map_ops.mmio)        return false_t;
            if (!par->map)                 return false_t;

            return par->map_ops.mmio->wr64 (
                par->map_ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_write
        (vp_map* par, void* par_mmio, void* par_buf, u64_t par_len) {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->map_ops.mmio)        return false_t;
            if (!par->map)                 return false_t;

            return par->map_ops.mmio->write (
                par->map_ops.mmio,
                par_mmio     ,
                par_buf      ,
                par_len
            );
}