#ifndef __CORE_HYPERV_DETAILS_CORE_H__
#define __CORE_HYPERV_DETAILS_CORE_H__

#include <obj.h>

#include <Windows.h>
#include <WinHvPlatform.h>
#include <WinHvPlatformDefs.h>
#include <WinHvEmulation.h>

bool_t core_init  ();
void   core_deinit();

#endif