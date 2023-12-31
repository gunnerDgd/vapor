#include "map.h"
#include "map_key.h"

#include "mmu.h"

#include "core.h"
#include "map/mmio.h"
#include "map/pio.h"

obj_trait vp_map_trait         = {
        .on_new   = &vp_map_new  ,
        .on_clone = &vp_map_clone,
        .on_ref   = 0            ,
        .on_del   = &vp_map_del  ,
        .size     = sizeof(vp_map)
};

obj_trait *vp_map_t = &vp_map_trait;

bool_t 
    vp_map_new
        (vp_map* par_map, u32_t par_count, va_list par) {
            if (kvm < 0)        return false_t;
            if (par_count != 2) return false_t;

            par_map->begin = va_arg(par, u64_t)           ;
            par_map->end   = va_arg(par, u64_t)           ;
            par_map->size  = par_map->end - par_map->begin;

            if (par_map->begin >= par_map->end)                       return false_t;
            if (par_map->size == 0)                                   return false_t;
            if (!make_at(&par_map->sub, map_t) from(1, vp_map_key_t)) return false_t;
            return true_t;
}

bool_t 
    vp_map_clone
        (vp_map* par, vp_map* par_clone) {
            return false_t;
}

bool_t
    vp_map_del
        (vp_map* par)                                                     {
            if (par->ops.pio)  par->ops.ops_pio->unmap(par->ops.pio , par);
            if (par->ops.mmio) par->ops.ops_pio->unmap(par->ops.mmio, par);
            if (par->sup)                            {
                map_pop(&par->sup->sub, par->sup_hnd);
                del    (&par->sub);
                del    (par->sup) ;
            }

            del(par->mmu);


}

vp_map*
    vp_map_sup
        (vp_map* par)                              {
            if (!par)                      return 0;
            if (trait_of(par) != vp_map_t) return 0;

            return par->sup;
}

vp_map*
    vp_map_sub_next
        (vp_map* par, vp_map* par_next)            {
            if (!par)                      return 0;
            if (trait_of(par) != vp_map_t) return 0;

            map_elem ret_it = map_next(par_next->sup_hnd); if (ret_it == map_end(&par->sub)) return 0;
            vp_map  *ret    = map_get (ret_it)           ; if (!ret)                         return 0;
            return   ret;
}

vp_map*
    vp_map_sub
        (vp_map* par, vp_map* par_sub)                  {
            if (!par)                           return 0;
            if (!par_sub)                       return 0;
            if (trait_of(par)     != vp_map_t)  return 0;
            if (trait_of(par_sub) != vp_map_t)  return 0;
            if (!vp_map_eq(par, par_sub))       return 0;

            if (par_sub->sup)                   return 0;
            if (par_sub->sup_hnd)               return 0;
            if (par_sub->mmu)                   return 0;

            if (vp_map_free(par))                                           {
                vp_map *sub = make (vp_map_t) from (2, par->begin, par->end);
                if    (!sub) return 0;
                
                sub->sup_hnd = map_push(&par->sub, sub);
                sub->sup     = ref(par)                ;
                sub->mmu     = ref(par->mmu)           ;

                del(sub);
            }

            vp_map *sub = vp_map_find(par, par_sub->begin, par_sub->size);
            if (!sub)             return 0;
            if (vp_map_pio (sub)) return 0;
            if (vp_map_mmio(sub)) return 0;
            if (vp_map_mem (sub)) return 0;
            if (vp_map_sect(sub)) return vp_map_sub(sub, par_sub);

            vp_map* begin = make (vp_map_t) from (2, sub    ->begin, par_sub->begin);
            vp_map* end   = make (vp_map_t) from (2, par_sub->end  , sub    ->end)  ;

            del(sub);
            if (begin)                                     {
                begin->sup_hnd = map_push(&par->sub, begin);
                begin->sup     = ref(par)                  ;
                begin->mmu     = ref(par->mmu)             ;
            }

            par_sub->sup_hnd = map_push(&par->sub, par_sub);
            par_sub->sup     = ref(par)     ;
            par_sub->mmu     = ref(par->mmu);

            if (end)                                   {
                end->sup_hnd = map_push(&par->sub, end);
                end->sup     = ref(par)                ;
                end->mmu     = ref(par->mmu)           ;
            }

            del   (begin)  ;
            del   (end)    ;
            del   (par_sub);
            return par_sub ;
}

vp_map*
    vp_map_find
        (vp_map* par, u64_t par_addr, u64_t par_size) {
            if (!par)                      return 0;
            if (trait_of(par) != vp_map_t) return 0;

            vp_map ret_key;
            if (!make_at(&ret_key, vp_map_t) from (2, par_addr, par_addr + par_size))
                return 0;

            map_elem ret_it = map_find(&par->sub, &ret_key); if (ret_it == map_end(&par->sub)) return 0;
            vp_map  *ret    = map_get (ret_it)             ; if (!ret)                         return 0;

            del  (&ret_key);
            return ret     ;
}

bool_t
    vp_map_free
        (vp_map* par)                                    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;

            if (par->ops.pio)              return false_t;
            if (par->ops.mmio)             return false_t;
            if (par->ops.mem)              return false_t;
            if (!map_empty(&par->sub))     return false_t;
            return true_t;
}

bool_t
    vp_map_sect
        (vp_map* par)                                    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;

            if (par->ops.pio)              return false_t;
            if (par->ops.mmio)             return false_t;
            if (par->ops.mem)              return false_t;

            return !map_empty(&par->sub);
}

bool_t
    vp_map_mmio
        (vp_map* par)                                    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->ops.mmio)            return false_t;

            return true_t;
}

bool_t
    vp_map_pio
        (vp_map* par)                                    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->ops.pio)             return false_t;

            return true_t;
}

bool_t
    vp_map_mem
        (vp_map* par)                                    {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_map_t) return false_t;
            if (!par->ops.mem)             return false_t;

            return true_t;
}

u64_t
    vp_map_begin
        (vp_map* par)                               {
            if (!par)                      return -1;
            if (trait_of(par) != vp_map_t) return -1;

            return par->begin;
}

u64_t
    vp_map_end
        (vp_map* par)                               {
            if (!par)                      return -1;
            if (trait_of(par) != vp_map_t) return -1;

            return par->end;
}

u64_t
    vp_map_size
        (vp_map* par)                              {
            if (!par)                      return 0;
            if (trait_of(par) != vp_map_t) return 0;

            return par->size;
}