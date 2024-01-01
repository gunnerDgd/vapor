project                   (vapor-example)
add_executable            (core-sys core/sys.c)
target_link_libraries     (core-sys build build-arch build-arch-asm vapor-core)
target_include_directories(core-sys PRIVATE ../include)

add_executable            (core-map core/map.c
)
target_link_libraries     (core-map build build-arch build-arch-asm vapor-core)
target_include_directories(core-map PRIVATE ../include)

add_executable            (core-pio core/pio.c)
target_link_libraries     (core-pio build build-arch build-arch-asm vapor-core)
target_include_directories(core-pio PRIVATE ../include)