#include "mmio.h"
#include "../map.h"

bool_t
    vp_mmio_map
        (vp_map* par, vp_mmio_ops* par_ops, obj* par_mmio) {
            if (!par)                      return false_t;
            if (!par_ops)                  return false_t;
            if (!par_mmio)                 return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (par->ops.mem)              return false_t;

            if (!par_ops->map)             return false_t;
            if (!par_ops->unmap)           return false_t;

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

            par->ops.ops_mmio = par_ops ;
            par->ops.mmio     = par_mmio;

            return true_t;
}

bool_t
    vp_mmio_rd8
        (vp_map* par, void* par_mmio, u8_t* par_buf)     {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->ops.ops_mmio)        return false_t;
            if (!par->ops.mmio)            return false_t;

            return par->ops.ops_mmio->rd8 (
                par->ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_rd16
        (vp_map* par, void* par_mmio, u16_t* par_buf)    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->ops.ops_mmio)        return false_t;
            if (!par->ops.mmio)            return false_t;

            return par->ops.ops_mmio->rd16 (
                par->ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_rd32
        (vp_map* par, void* par_mmio, u32_t* par_buf)    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->ops.ops_mmio)        return false_t;
            if (!par->ops.mmio)            return false_t;

            return par->ops.ops_mmio->rd32 (
                par->ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_rd64
        (vp_map* par, void* par_mmio, u64_t* par_buf)    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->ops.ops_mmio)        return false_t;
            if (!par->ops.mmio)            return false_t;

            return par->ops.ops_mmio->rd64 (
                par->ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_read
        (vp_map* par, void* par_mmio, void* par_buf, u64_t par_len) {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->ops.ops_mmio)        return false_t;
            if (!par->ops.mmio)            return false_t;

            return par->ops.ops_mmio->read (
                par->ops.mmio,
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
            if (!par->ops.ops_mmio)        return false_t;
            if (!par->ops.mmio)            return false_t;

            return par->ops.ops_mmio->wr8 (
                par->ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_wr16
        (vp_map* par, void* par_mmio, u16_t* par_buf)    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->ops.ops_mmio)        return false_t;
            if (!par->ops.mmio)            return false_t;

            return par->ops.ops_mmio->wr16 (
                par->ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_wr32
        (vp_map* par, void* par_mmio, u32_t* par_buf)    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->ops.ops_mmio)        return false_t;
            if (!par->ops.mmio)            return false_t;

            return par->ops.ops_mmio->wr32 (
                par->ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_wr64
        (vp_map* par, void* par_mmio, u64_t* par_buf)    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->ops.ops_mmio)        return false_t;
            if (!par->ops.mmio)            return false_t;

            return par->ops.ops_mmio->wr64 (
                par->ops.mmio,
                par_mmio     ,
                par_buf
            );
}

bool_t
    vp_mmio_write
        (vp_map* par, void* par_mmio, void* par_buf, u64_t par_len) {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->ops.ops_mmio)        return false_t;
            if (!par->ops.mmio)            return false_t;

            return par->ops.ops_mmio->write (
                par->ops.mmio,
                par_mmio     ,
                par_buf      ,
                par_len
            );
}