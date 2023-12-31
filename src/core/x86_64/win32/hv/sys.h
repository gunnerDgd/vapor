#ifndef __DETAILS_HV_SYS_H__
#define __DETAILS_HV_SYS_H__

#include "obj.h"
#include "list.h"

#define           sys_state_none 0
#define           sys_state_run  1
#define           sys_state_exit 2
#define           sys_state_term 3
extern obj_trait *sys_t   ;
typedef struct    sys     {
    obj         head      ;
    void*       sys       ;
    list        vcpu      ;
    u64_t       vcpu_count;
    struct mmu* mmu       ;
}   sys;

bool_t       sys_new  (sys*, u32_t, va_list);
bool_t       sys_clone(sys*, sys*)          ;
void         sys_del  (sys*, sys*)          ;

struct vcpu* sys_vcpu (sys*, struct vcpu*)  ;
struct mmu*  sys_mmu  (sys*)                ;

#endif