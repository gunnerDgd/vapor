#include "dev.h"
#include "../map.h"

bool_t 
    map_dev_new
        (map_dev* par_dev, u32_t par_count, va_list par) {
            par_dev->map = va_arg(par, map*);
            if (!par_dev->map)                   return false_t;
            if (trait_of(par_dev->map) != map_t) return false_t;

            par_dev->dev     = va_arg(par, obj*)        ; if (!par_dev->dev)     return false_t;
            par_dev->dev_ops = va_arg(par, map_dev_ops*); if (!par_dev->dev_ops) return false_t;
            par_dev->map     = ref(par_dev->map)        ;
            par_dev->dev     = ref(par_dev->dev)        ;

            return true_t;
}

bool_t 
    map_dev_clone
        (map_dev* par, map_dev* par_clone) {
            return false_t;
}

void
    map_dev_del
        (map_dev* par)   {
            del(par->map);
            del(par->dev);
}

bool_t 
    map_dev_rd8
        (map_dev* par, u8_t* par_rd)                      {
            if (!par)                       return false_t;
            if (trait_of(par) != map_dev_t) return false_t;
            if (!par->dev_ops->rd8)         return false_t;

            return par->dev_ops->rd8(par->dev, par_rd);
}

bool_t 
    map_dev_rd16
        (map_dev* par, u16_t* par_rd)                     {
            if (!par)                       return false_t;
            if (trait_of(par) != map_dev_t) return false_t;
            if (!par->dev_ops->rd16)        return false_t;

            return par->dev_ops->rd16(par->dev, par_rd);
}

bool_t 
    map_dev_rd32
        (map_dev* par, u32_t* par_rd)                     {
            if (!par)                       return false_t;
            if (trait_of(par) != map_dev_t) return false_t;
            if (!par->dev_ops->rd32)        return false_t;

            return par->dev_ops->rd8(par->dev, par_rd);
}

bool_t 
    map_dev_rd64
        (map_dev* par, u64_t* par_rd)                     {
            if (!par)                       return false_t;
            if (trait_of(par) != map_dev_t) return false_t;
            if (!par->dev_ops->rd64)        return false_t;

            return par->dev_ops->rd64(par->dev, par_rd);
}

bool_t 
    map_dev_read
        (map_dev* par, void* par_rd, u64_t par_len)       {
            if (!par)                       return false_t;
            if (trait_of(par) != map_dev_t) return false_t;
            if (!par->dev_ops->read)        return false_t;

            return par->dev_ops->read(par->dev, par_rd, par_len);
}

bool_t 
    map_dev_wr8
        (map_dev* par, u8_t par_wr)                       {
            if (!par)                       return false_t;
            if (trait_of(par) != map_dev_t) return false_t;
            if (!par->dev_ops->wr8)         return false_t;

            return par->dev_ops->wr8(par->dev, par_wr);
}

bool_t 
    map_dev_wr16
        (map_dev* par, u16_t par_wr)                      {
            if (!par)                       return false_t;
            if (trait_of(par) != map_dev_t) return false_t;
            if (!par->dev_ops->wr16)        return false_t;

            return par->dev_ops->wr16(par->dev, par_wr);
}

bool_t 
    map_dev_wr32
        (map_dev* par, u32_t par_wr)                      {
            if (!par)                       return false_t;
            if (trait_of(par) != map_dev_t) return false_t;
            if (!par->dev_ops->wr32)        return false_t;

            return par->dev_ops->wr32(par->dev, par_wr);
}

bool_t 
    map_dev_wr64
        (map_dev* par, u64_t* par_wr)                     {
            if (!par)                       return false_t;
            if (trait_of(par) != map_dev_t) return false_t;
            if (!par->dev_ops->wr64)        return false_t;

            return par->dev_ops->wr64(par->dev, par_wr);
}

bool_t 
    map_dev_write
        (map_dev* par, void* par_wr, u64_t par_len)       {
            if (!par)                       return false_t;
            if (trait_of(par) != map_dev_t) return false_t;
            if (!par->dev_ops->write)       return false_t;

            return par->dev_ops->write(par->dev, par_wr, par_len);
}