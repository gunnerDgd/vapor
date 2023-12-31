#include "mem.h"
#include "../map.h"

bool_t 
    map_mem_new
        (map_mem* par_mem, u32_t par_count, va_list par) {
            par_mem->map = va_arg(par, map*)    ;
            par_mem->res = va_arg(par, mem_res*);

            if (!par_mem->map)                   return false_t;
            if (trait_of(par_mem->map) != map_t) return false_t;

            if (!par_mem->res)                   return false_t;
            if (!par_mem->res->on_new)           return false_t;
            if (!par_mem->res->on_del)           return false_t;
            if (!par_mem->res->on_mem_new)       return false_t;
            if (!par_mem->res->on_mem_del)       return false_t;

            par_mem->mem = mem_new(par_mem->res, par_mem->map->size); if (!par_mem->mem) return false_t;
            par_mem->map = ref(par_mem->map)                        ;
            par_mem->res = ref(par_mem->res)                        ;
            return true_t;
}

bool_t 
    map_mem_clone
        (map_mem* par, map_mem* par_mem) {
            return false_t;
}

void
    map_mem_del
        (map_mem* par)                 {
            del(par->map)              ;
            mem_del(par->res, par->mem);
}