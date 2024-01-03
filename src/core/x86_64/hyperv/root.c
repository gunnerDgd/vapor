#include "root.h"
#include "node.h"

void* 
    vp_root_node
        (vp_root* par, void* par_node)                    {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_root_t) return false_t;
            if (!par_node)                          {
                void*  ret  = list_begin(&par->node);
                if    (ret == list_end  (&par->node)) return 0;
                return ret;
            }

            vp_node* ret = list_get(par_node);
            if (!ret)                       return 0;
            if (trait_of(ret) != vp_node_t) return 0;
            if (ret->root != par)           return 0;
            
            par_node = list_next(par_node); if (par_node == list_end(&par->node)) return 0;
            return par_node;
}

void* 
    vp_root_map
        (vp_root* par, u64_t par_begin, u64_t par_end) {
            if (!par)                       return 0;
            if (trait_of(par) != vp_root_t) return 0;

            list_for (&par->node, node)                           {
                void* ret = vp_node_map (node, par_begin, par_end);
                if   (ret) return ret;
            }

            return 0;
}

void* 
    vp_root_map_find
        (vp_root* par, u64_t par_addr, u64_t par_len) {
            if (!par)                       return 0;
            if (trait_of(par) != vp_root_t) return 0;

            list_for (&par->node, node)                              {
                void* ret = vp_node_map_find(node, par_addr, par_len);
                if   (ret) return ret;
            }

            return 0;
}

void* 
    vp_port_map
        (vp_root* par, u64_t par_begin, u64_t par_end) {
            if (!par)                       return 0;
            if (trait_of(par) != vp_root_t) return 0;

            vp_map *map = make (vp_map_t) from (2, par_begin, par_end);
            void   *ret = 0;

            if (!map)                                 return 0;
            if (!(ret = vp_mmu_map(&par->port, map))) {
                del(map);
                return 0;
            }

            map->type = vp_map_type_pio;
            return ret;
}

void* 
    vp_port_find
        (vp_root* par, u64_t par_addr, u64_t par_len) {
            if (!par)                       return 0;
            if (trait_of(par) != vp_root_t) return 0;
            
            void* ret = vp_mmu_find(&par->port, par_addr, par_len);
            return ret;
}