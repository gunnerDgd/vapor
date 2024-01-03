#ifndef __VP_H__
#define __VP_H__

#include "core.h"
#include "arch.h"

#define vp_main()             \
    int main_run();           \
    int main()       {        \
        core_init  ();        \
        int ret = main_run ();\
        core_deinit();        \
    }                         \
    int main_run()

#endif