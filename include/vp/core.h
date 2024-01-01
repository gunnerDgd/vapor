#ifndef __VP_CORE_H__
#define __VP_CORE_H__

#include <obj.h>

#include "core/sys.h"
#include "core/cpu.h"

#include "core/map.h"
#include "core/map/mmio.h"
#include "core/map/pio.h"
#include "core/map/mem.h"

#include "core/mmu.h"
#include "core/run.h"
#include "core/run/mmio.h"
#include "core/run/pio.h"
#include "core/run/halt.h"

bool_t core_init  ();
bool_t core_deinit();

#endif