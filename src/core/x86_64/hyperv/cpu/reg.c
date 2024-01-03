#include "reg.h"

bool_t
    vp_reg_get
        (vp_reg* par, u64_t par_reg, u64_t* par_get)     {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_reg_t) return false_t;
            if (par_reg > vp_rflags)       return false_t;

            *par_get = par->reg[par_reg].Reg64;
            return true_t;
}

bool_t
    vp_reg_set
        (vp_reg* par, u64_t par_reg, u64_t par_set)      {
            if (!par)                      return false_t;
            if (trait_of(par) != vp_reg_t) return false_t;
            if (par_reg > vp_rflags)       return false_t;

            par->reg[par_reg].Reg64 = par_set;
            return true_t;
}