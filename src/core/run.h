#ifndef __CORE_CPU_H__
#define __CORE_CPU_H__

#ifdef PRESET_ARCH_X86_64
#ifdef PRESET_LINUX_KVM
#include "x86_64/linux/kvm/run.h"

#include "x86_64/linux/kvm/run/mmio.h"
#include "x86_64/linux/kvm/run/pio.h"
#include "x86_64/linux/kvm/run/halt.h"
#endif
#endif

#endif