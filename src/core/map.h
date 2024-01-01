#ifndef __CORE_MAP_H__
#define __CORE_MAP_H__

#ifdef PRESET_ARCH_X86_64
#ifdef PRESET_LINUX_KVM
#include "x86_64/linux/kvm/map.h"

#include "x86_64/linux/kvm/map/mem.h"
#include "x86_64/linux/kvm/map/mmio.h"
#include "x86_64/linux/kvm/map/pio.h"
#endif
#endif

#endif