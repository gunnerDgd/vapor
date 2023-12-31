#include "map.h"
#include "mmu.h"

bool_t 
    map_new
        (map* par_map, u32_t par_count, va_list par)      {
            par_map->begin = va_arg(par, u64_t)           ;
            par_map->end   = va_arg(par, u64_t)           ;
            par_map->size  = par_map->end - par_map->begin;       

            if (par_map->begin <= par_map->end)          return false_t;
            if (!make_at(&par_map->sub, list_t) from(0)) return false_t;
            if (par_count == 2)                          return true_t ;

            obj_trait *map_trait = va_arg(par, obj_trait*)                ; if (!map_trait) goto new_failed;
            obj       *map       = vmake (map_t) from (par_count - 3, par); if (!map)       goto new_failed;

            par_map->map = map;
            return true_t;
    new_failed:
            del (&par_map->sub);
            return false_t;
}

bool_t 
    map_clone
        (map* par, map* par_clone) {
            return false_t;
}

bool_t 
    map_del
        (map* par)                           {
            list_pop(&par->sup, par->sup_hnd);

            del(par->sup) ;
            del(par->mmu) ;

            del(&par->sub);
}

map* 
    map_sup
        (map* par)                              {
            if (!par)                   return 0;
            if (trait_of(par) != map_t) return 0;

            return par->sup;
}

map* 
    map_sub_next
        (map* par, map* par_next)               {
            if (!par)                   return 0;
            if (trait_of(par) != map_t) return 0;

            if (!par_next)                               {
                list_elem *ret_it = list_begin(&par->sub);
                map       *ret    = list_get  (ret_it)   ;
                return     ret;
            }

            if (trait_of(par_next) != map_t) return 0;
            if (par_next->sup != par)        return 0;

            list_elem *ret_it = list_next(par_next->sup_hnd);
            map       *ret    = list_get (ret_it)           ;
            return     ret;
}

map*
    map_sub
        (map* par, map* par_sub)                     {
            if (!par)                        return 0;
            if (!par_sub)                    return 0;
            if (trait_of(par)     != map_t)  return 0;
            if (trait_of(par_sub) != map_t)  return 0;

            if (par_sub->begin < par->begin) return 0;
            if (par_sub->end   > par->end)   return 0;
            if (par_sub->sup)                return 0;
            if (par_sub->sup_hnd)            return 0;
            if (par_sub->mmu)                return 0;

            if (list_empty(&par->sub))                               {
                map *sub = make(map_t) from (2, par->begin, par->end);
                if (!sub) return 0;
                
                sub->sup_hnd = list_push_back(&par->sub, sub);
                sub->sup     = ref(par)                      ;
                sub->mmu     = ref(par->mmu)                 ;

                del(sub);
            }

            list_elem sub_it = map_find(par, par_sub->begin, par_sub->size);
            map*      sub    = list_get(sub_it)                            ;

            if (!sub_it)                return 0;
            if (!sub)                   return 0;
            if (sub->map)               return 0;
            if (!list_empty(&sub->sub)) return map_sub(sub, par_sub);

            if (sub->begin == par_sub->begin) {
                list_set(sub_it, par_sub);
                if (sub->end != par_sub->end)                                   {
                    sub          = make (map_t) from (2, par_sub->end, par->end);
                    sub->sup_hnd = list_push(&par->sub, sub, sub_it);
                }

                par_sub->mmu = ref(par->mmu);
                par_sub->sup = ref(par)     ; del(par_sub);

                return par_sub;
            }
            
            par_sub->sup_hnd = list_push(&par->sub, par_sub, sub_it);
            if (sub->end != par_sub->end)                                 {
                sub          = make(map_t) from(2, par_sub->end, sub->end);
                sub->sup_hnd = list_push(&par->sub, sub, par_sub->sup_hnd);
            }

            par_sub->mmu = ref(par->mmu);
            par_sub->sup = ref(par)     ; del(par_sub);

            return par_sub;
}

map*
    map_find
        (map* par, u64_t par_addr, u64_t par_size) {
            if (!par)                   return 0;
            if (trait_of(par) != map_t) return 0;

            list_for (&par->sub, sub_it)                        {
                map *sub = list_get(sub_it)                     ;
                if (!sub)                               continue;
                if (sub->begin >  par_addr)             continue;
                if (sub->end   <  par_addr)             continue;
                if (sub->end   < (par_addr + par_size)) continue;

                return sub;
            }

            return 0;
}