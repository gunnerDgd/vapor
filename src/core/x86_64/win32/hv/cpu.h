#ifndef __DETAILS_HV_VCPU_H__
#define __DETAILS_HV_VCPU_H__

#include "obj.h"
#include "list.h"

extern obj_trait* vcpu_t;
typedef struct    vcpu  {
    obj         head   ;
    struct sys* sys    ;
    list_elem   sys_hnd;
    u64_t       vcpu   ;
}   vcpu;

bool_t      vcpu_new  (vcpu*, u32_t, va_list);
bool_t      vcpu_clone(vcpu*, vcpu*)         ;
void        vcpu_del  (vcpu*)                ;
struct run* vcpu_run  (vcpu*)                ;

#endif