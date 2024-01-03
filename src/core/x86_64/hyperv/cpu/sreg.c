#include "sreg.h"

u64_t
    vp_desc_base
        (vp_sreg* par, u64_t par_desc, u64_t* par_base) {
            if (!par)                       return -1;
            if (trait_of(par) != vp_sreg_t) return -1;
            if (par_desc > vp_idt)          return -1;
            if (par_desc < vp_gdt)          return -1;

            u64_t  ret = par->sreg[par_desc].Table.Base; if (par_base) par->sreg[par_desc].Table.Base = *par_base;
            return ret;
}

u64_t
    vp_desc_limit
        (vp_sreg* par, u64_t par_desc, u64_t* par_limit) {
            if (!par)                       return -1;
            if (trait_of(par) != vp_sreg_t) return -1;
            if (par_desc > vp_idt)          return -1;
            if (par_desc < vp_gdt)          return -1;

            u64_t  ret = par->sreg[par_desc].Table.Limit; if (par_limit) par->sreg[par_desc].Table.Limit = *par_limit;
            return ret;
}

u64_t
    vp_seg_base
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->sreg[par_seg].Segment.Base; if (par_buf) par->sreg[par_seg].Segment.Base = *par_buf;
            return ret;
}

u64_t
    vp_seg_limit
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->sreg[par_seg].Segment.Limit; if (par_buf) par->sreg[par_seg].Segment.Limit = *par_buf;
            return ret;
}

u64_t
    vp_seg_selector
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->sreg[par_seg].Segment.Selector; if (par_buf) par->sreg[par_seg].Segment.Selector = *par_buf;
            return ret;
}

u64_t
    vp_seg_type
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->sreg[par_seg].Segment.SegmentType; if (par_buf) par->sreg[par_seg].Segment.SegmentType = *par_buf;
            return ret;
}

u64_t
    vp_seg_present
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->sreg[par_seg].Segment.Present; if (par_buf) par->sreg[par_seg].Segment.Present = *par_buf;
            return ret;
}

u64_t
    vp_seg_priv
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->sreg[par_seg].Segment.DescriptorPrivilegeLevel; if (par_buf) par->sreg[par_seg].Segment.DescriptorPrivilegeLevel = *par_buf;
            return ret;
}

u64_t
    vp_seg_size
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->sreg[par_seg].Segment.Default; if (par_buf) par->sreg[par_seg].Segment.Default = *par_buf;
            return ret;
}

u64_t
    vp_seg_desc
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->sreg[par_seg].Segment.NonSystemSegment; if (par_buf) par->sreg[par_seg].Segment.NonSystemSegment = *par_buf;
            return ret;
}

u64_t
    vp_seg_long
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->sreg[par_seg].Segment.Long; if (par_buf) par->sreg[par_seg].Segment.Long = *par_buf;
            return ret;
}

u64_t
    vp_seg_gran
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->sreg[par_seg].Segment.Granularity; if (par_buf) par->sreg[par_seg].Segment.Granularity = *par_buf;
            return ret;
}

u64_t
    vp_seg_avail
        (vp_sreg* par, u64_t par_seg, u64_t* par_buf)     {
            if (!par)                       return false_t;
            if (trait_of(par) != vp_sreg_t) return false_t;
            if (par_seg > vp_ldt)           return false_t;

            u64_t  ret = par->sreg[par_seg].Segment.Available; if (par_buf) par->sreg[par_seg].Segment.Available = *par_buf;
            return ret;
}