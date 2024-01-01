#include "sreg.h"
#include "../core.h"

#include <sys/ioctl.h>

obj_trait vp_sreg_trait     = {
    .on_new   = &vp_sreg_new  ,
    .on_clone = &vp_sreg_clone,
    .on_ref   = 0             ,
    .on_del   = &vp_sreg_del  ,
    .size     = sizeof(vp_sreg)
};

obj_trait *vp_sreg_t = &vp_sreg_trait;

bool_t
    vp_sreg_new
        (vp_sreg* par_sreg, u32_t par_count, va_list par) {
            if (kvm < 0)        return false_t;
            if (par_count != 1) return false_t;

            par_sreg->cpu = va_arg(par, vp_cpu*);
            if (!par_sreg->cpu)                                                return false_t;
            if (trait_of(par_sreg->cpu) != vp_cpu_t)                           return false_t;
            if (ioctl(par_sreg->cpu->cpu, KVM_GET_SREGS, &par_sreg->sreg) < 0) return false_t;

            par_sreg->cpu  = ref(par_sreg->cpu) ;
            par_sreg->seg  = &par_sreg->sreg.cs ;
            par_sreg->desc = &par_sreg->sreg.gdt;
            return true_t;
}

bool_t
    vp_sreg_clone
        (vp_sreg* par, vp_sreg* par_clone) {
            return false_t;
}

void
    vp_sreg_del
        (vp_sreg* par)                                     {
            ioctl(par->cpu->cpu, KVM_SET_SREGS, &par->sreg);
            del  (par->cpu)                                ;
}

u64_t
    vp_desc_base
        (vp_sreg* par, u64_t par_desc, u64_t* par_base) {
            if (!par)                       return -1;
            if (trait_of(par) != vp_sreg_t) return -1;
            if (par_desc > vp_idt)          return -1;

            u64_t  ret = par->desc[par_desc].base; if (par_base) par->desc[par_desc].base = *par_base;
            return ret;
}

u64_t
    vp_desc_limit
        (vp_sreg* par, u64_t par_desc, u64_t* par_limit) {
            if (!par)                       return -1;
            if (trait_of(par) != vp_sreg_t) return -1;
            if (par_desc > vp_idt)          return -1;

            u64_t  ret = par->desc[par_desc].limit; if (par_limit) par->desc[par_desc].limit = *par_limit;
            return ret;
}

u64_t
    vp_seg_base
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->seg[par_seg].base; if (par_buf) par->seg[par_seg].base = *par_buf;
            return ret;
}

u64_t
    vp_seg_limit
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->seg[par_seg].limit; if (par_buf) par->seg[par_seg].limit = *par_buf;
            return ret;
}

u64_t
    vp_seg_selector
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->seg[par_seg].selector; if (par_buf) par->seg[par_seg].selector = *par_buf;
            return ret;
}

u64_t
    vp_seg_type
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->seg[par_seg].type; if (par_buf) par->seg[par_seg].type = *par_buf;
            return ret;
}

u64_t
    vp_seg_present
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->seg[par_seg].present; if (par_buf) par->seg[par_seg].present = *par_buf;
            return ret;
}

u64_t
    vp_seg_priv
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->seg[par_seg].dpl; if (par_buf) par->seg[par_seg].dpl = *par_buf;
            return ret;
}

u64_t
    vp_seg_size
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->seg[par_seg].db; if (par_buf) par->seg[par_seg].db = *par_buf;
            return ret;
}

u64_t
    vp_seg_desc
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->seg[par_seg].s; if (par_buf) par->seg[par_seg].s = *par_buf;
            return ret;
}

u64_t
    vp_seg_long
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->seg[par_seg].l; if (par_buf) par->seg[par_seg].l = *par_buf;
            return ret;
}

u64_t
    vp_seg_gran
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->seg[par_seg].g; if (par_buf) par->seg[par_seg].g = *par_buf;
            return ret;
}

u64_t
    vp_seg_avail
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->seg[par_seg].avl; if (par_buf) par->seg[par_seg].avl = *par_buf;
            return ret;
}