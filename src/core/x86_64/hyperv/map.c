#include "map.h"

#include "root.h"
#include "node.h"

#include "details/core.h"

void* 
    vp_map_mmio
        (void* par, vp_map_ops* par_ops, obj* par_mmio)                            {
            if (!par)                          return 0; vp_map* map = map_get(par);
            if (!map)                          return 0;
            if (trait_of(map) != vp_map_t)     return 0;
            if (map->type != vp_map_type_none) return 0;

            if (map->map_ops) return 0;
            if (map->map)     return 0;

            if (!par_ops)        return 0;
            if (!par_ops->read)  return 0;
            if (!par_ops->write) return 0;
            if (!par_ops->map)   return 0;
            if (!par_ops->unmap) return 0;

            vp_mmu *mmu = map->mmu ; 
            if (!mmu)                         return 0;
            if (trait_of(mmu)  != vp_mmu_t)   return 0;
            if (!par_ops->map(par_mmio, par)) return 0;

            map->type    = vp_map_type_mmio;
            map->map_ops = par_ops         ;
            map->map     = ref(par_mmio)   ;

            return par;
}

void* 
    vp_map_mem
        (void* par, void* par_mem)                                                 {
            if (!par)                          return 0; vp_map* map = map_get(par);
            if (!par_mem)                      return 0;
            if (!map)                          return 0;
            if (trait_of(map) != vp_map_t)     return 0;
            if (map->type != vp_map_type_none) return 0;

            vp_mmu  *mmu  = map ->mmu ; if (!mmu)  return 0;
            vp_node *node = mmu ->node; if (!node) return 0;
            vp_root *root = node->root; if (!root) return 0;

            if (trait_of(mmu)  != vp_mmu_t)  return 0;
            if (trait_of(node) != vp_node_t) return 0;
            if (trait_of(root) != vp_root_t) return 0;

            map->type = vp_map_type_mem;
            map->map_ops = 0           ;
            map->map     = par_mem     ;

            HRESULT res = WHvMapGpaRange (
                root->root, 
                par_mem   ,
                map->begin,
                map->size ,
                7
            );

            if (res != S_OK) return 0;
            return par;
}

void* 
    vp_map_pio
        (void* par, vp_map_ops* par_ops, obj* par_mmio)                           {
            if (!par)                         return 0; vp_map* map = map_get(par);
            if (!map)                         return 0;
            if (trait_of(map) != vp_map_t)    return 0;
            if (map->type != vp_map_type_pio) return 0;

            if (map->map_ops) return 0;
            if (map->map)     return 0;

            if (!par_ops)        return 0;
            if (!par_ops->read)  return 0;
            if (!par_ops->write) return 0;
            if (!par_ops->map)   return 0;
            if (!par_ops->unmap) return 0;

            vp_mmu *mmu = map->mmu ; 
            if (!mmu)                         return 0;
            if (trait_of(mmu)  != vp_mmu_t)   return 0;
            if (!par_ops->map(par_mmio, par)) return 0;

            map->type    = vp_map_type_mmio;
            map->map_ops = par_ops         ;
            map->map     = ref(par_mmio)   ;

            return par;
}

u64_t
    vp_map_type
        (void* par)                                                            {
            if (!par)                      return 0; vp_map* map = map_get(par);
            if (!map)                      return 0;
            if (trait_of(map) != vp_map_t) return 0;

            return map->type;
}

u64_t
    vp_map_begin
        (void* par)                                                            {
            if (!par)                      return 0; vp_map* map = map_get(par);
            if (!map)                      return 0;
            if (trait_of(map) != vp_map_t) return 0;

            return map->begin;
}

u64_t
    vp_map_end
        (void* par)                                                            {
            if (!par)                      return 0; vp_map* map = map_get(par);
            if (!map)                      return 0;
            if (trait_of(map) != vp_map_t) return 0;

            return map->end;
}

u64_t
    vp_map_size
        (void* par)                                                            {
            if (!par)                      return 0; vp_map* map = map_get(par);
            if (!map)                      return 0;
            if (trait_of(map) != vp_map_t) return 0;

            return map->size;
}

bool_t 
    vp_map_read
        (void* par, void* par_addr, void* par_buf, u64_t par_len) {
            if (!par)     return 0;
            if (!par_buf) return 0; vp_map* map = map_get(par);

            if (!map)                      return 0;
            if (trait_of(map) != vp_map_t) return 0;

            switch (map->type)                       {
                case vp_map_type_none: return false_t;
                case vp_map_type_mmio:
                case vp_map_type_pio : return map->map_ops->read(map->map, par_addr, par_buf, par_len);
                case vp_map_type_mem :                       {
                    u64_t off  = (u64_t)par_addr - map->begin;
                    u64_t addr = (u64_t)map->map + off       ; if (par_len > (map->size - off)) return false_t;

                    mem_copy(par_buf, addr, par_len);
                    return true_t;
                }
            }

            return false_t;
}

bool_t 
    vp_map_write
        (void* par, void* par_addr, void* par_buf, u64_t par_len) {
            if (!par)     return 0;
            if (!par_buf) return 0; vp_map* map = map_get(par);

            if (!map)                      return 0;
            if (trait_of(map) != vp_map_t) return 0;

            switch (map->type)                       {
                case vp_map_type_none: return false_t;
                case vp_map_type_mmio:
                case vp_map_type_pio : return map->map_ops->write(map->map, par_addr, par_buf, par_len);
                case vp_map_type_mem :                       {
                    u64_t off  = (u64_t)par_addr - map->begin;
                    u64_t addr = (u64_t)map->map + off       ; if (par_len > (map->size - off)) return false_t;

                    mem_copy(addr, par_buf, par_len);
                    return true_t;
                }
            }

            return false_t;
}