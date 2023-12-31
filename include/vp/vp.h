#ifndef __VP_H__
#define __VP_H__

#include "core.h"

#define vp_main()                   \
    int main_run();                 \
    int main    () {                \
        if (!core_init()) return -1;\
        main_run();                 \
        core_deinit();              \
    }                               \
    int main_run()

#endif