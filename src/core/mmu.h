#ifndef __CORE_CPU_H__
#define __CORE_CPU_H__

#ifdef PRESET_ARCH_X86_64
#ifdef PRESET_LINUX_KVM
#include "x86_64/linux/kvm/mmu.h"
#endif
#endif

#endif