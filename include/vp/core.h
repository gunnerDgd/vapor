#ifndef __CORE_H__
#define __CORE_H__

#include "core/cpu.h"
#include "core/map.h"
#include "core/node.h"
#include "core/root.h"

#include "core/run/halt.h"
#include "core/run/mmio.h"
#include "core/run/pio.h"

bool_t core_init  ();
void   core_deinit();

#endif