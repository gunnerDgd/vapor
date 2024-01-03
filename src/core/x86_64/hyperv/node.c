#include "node.h"

#include "root.h"
#include "cpu.h"

void* 
    vp_node_cpu     
        (void* par, void* par_cpu)                                   {
            if (!par)     return 0; vp_node *node = list_get(par)    ;
            if (!par_cpu)                          {
                void*  ret = list_begin(&node->cpu);
                if   (!ret)                         return 0;
                if    (ret == list_end(&node->cpu)) return 0;
                return ret;
            }

            vp_cpu* cpu = list_get(par_cpu);

            if (!node)                           return 0;
            if (trait_of(node) != vp_node_t)     return 0;

            if (!cpu)                            return 0;
            if (trait_of(cpu) != vp_cpu_t)       return 0;
            if (cpu->node != node)               return 0; par_cpu = list_next(par_cpu);
            if (par_cpu == list_end(&node->cpu)) return 0;
            
            return par_cpu;
}

void* 
    vp_node_map
        (void* par, u64_t par_begin, u64_t par_end)                                 {
            if (!par)                        return 0; vp_node* node = list_get(par);
            if (!node)                       return 0;
            if (trait_of(node) != vp_node_t) return 0;

            vp_map *ret_map = make (vp_map_t) from (2, par_begin, par_end);
            void   *ret     = vp_mmu_map(&node->mmu, ret_map);

            if (!ret_map) return 0;
            if (!ret)             {
                del   (ret_map);
                return ret     ;
            }

            return  ret;
}

void* 
    vp_node_map_find
        (void* par, u64_t par_addr, u64_t par_len)                                  {
            if (!par)                        return 0; vp_node* node = list_get(par);
            if (!node)                       return 0;
            if (trait_of(node) != vp_node_t) return 0;

            void  *ret = vp_mmu_find(&node->mmu, par_addr, par_len); if (!ret) return 0;
            return ret;
}

void* 
    vp_node_map_next
        (void* par, void* par_map)                                   {
            if (!par)     return 0; vp_node *node = list_get(par)    ;
            if (!par_map) return 0; vp_map  *map  = map_get (par_map);

            if (!node)                       return 0;
            if (trait_of(node) != vp_node_t) return 0;

            if (!map)                               return 0;
            if (trait_of(map) != vp_map_t)          return 0;
            if (map->mmu != &node->mmu)             return 0; par_map = map_next(par_map);
            if (par_map == map_end(&node->mmu.mmu)) return 0;

            return par_map;
}