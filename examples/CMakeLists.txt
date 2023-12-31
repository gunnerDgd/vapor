project                   (vapor-example)
add_executable            (core-core core/core.c
        ../include/vp/core/map/mem.h)
target_link_libraries     (core-core build build-arch build-arch-asm vapor-core)
target_include_directories(core-core PRIVATE ../include)

add_executable            (core-sys core/sys.c)
target_link_libraries     (core-sys build build-arch build-arch-asm vapor-core)
target_include_directories(core-sys PRIVATE ../include)

add_executable            (core-map core/map.c)
target_link_libraries     (core-map build build-arch build-arch-asm vapor-core)
target_include_directories(core-map PRIVATE ../include)