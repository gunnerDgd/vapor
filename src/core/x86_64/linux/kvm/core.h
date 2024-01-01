#ifndef __CORE_KVM_CORE_H__
#define __CORE_KVM_CORE_H__

#include <obj.h>

extern int kvm;

bool_t core_init  ();
void   core_deinit();

#endif