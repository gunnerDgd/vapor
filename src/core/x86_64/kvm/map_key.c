#include "map.h"
#include "map_key.h"

map_key vp_map_key_trait = {
    .eq = &vp_map_eq,
    .lt = &vp_map_lt,
    .gt = &vp_map_gt
};

map_key *vp_map_key_t = &vp_map_key_trait;

bool_t
    vp_map_eq
        (vp_map* par, vp_map* par_eq)                       {
            if (!par)                         return false_t;
            if (!par_eq)                      return false_t;

            if (trait_of(par)    != vp_map_t) return false_t;
            if (trait_of(par_eq) != vp_map_t) return false_t;

            return (par->begin <= par_eq->begin) && (par->end >= par_eq->end);
}

bool_t
    vp_map_gt
        (vp_map* par, vp_map* par_eq)                       {
            if (!par)                         return false_t;
            if (!par_eq)                      return false_t;

            if (trait_of(par)    != vp_map_t) return false_t;
            if (trait_of(par_eq) != vp_map_t) return false_t;

            return (par->begin < par_eq->begin) && (par->end < par_eq->end);
}

bool_t
    vp_map_lt
        (vp_map* par, vp_map* par_eq)                       {
            if (!par)                         return false_t;
            if (!par_eq)                      return false_t;

            if (trait_of(par)    != vp_map_t) return false_t;
            if (trait_of(par_eq) != vp_map_t) return false_t;

            return (par->begin > par_eq->begin) && (par->end > par_eq->end);
}