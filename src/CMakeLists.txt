add_library(vapor STATIC
        ../include/vp/core/cpu.h
        ../include/vp/arch/x86_64/reg.h
        ../include/vp/arch/x86_64/sreg.h
        ../include/vp/core/sys.h
        ../include/vp/core/mmu.h
        ../include/vp/core/map.h
        ../include/vp/core/map/mmio.h
        ../include/vp/core/map/pio.h
        ../include/vp/arch.h
        ../include/vp/core/run.h
        ../include/vp/core.h
        ../include/vp/core/run/pio.h
        ../include/vp/core/run/mmio.h
        ../include/vp/core/run/halt.h
        ../include/vp/vp.h
        core/run.h
        core.h
)

set_target_properties(vapor PROPERTIES LINKER_LANGUAGE C)

if   (WIN32)
    if   (PRESET_WIN32_HYPERV)
        add_library (vapor-core STATIC
                core/x86_64/win32/hv/sys.h
                core/x86_64/win32/hv/sys.c

                core/x86_64/win32/hv/cpu.h
                core/x86_64/win32/hv/cpu.c

                core/x86_64/win32/hv/mmu.h
                core/x86_64/win32/hv/mmu.c

                core/x86_64/win32/hv/run.h
                core/x86_64/win32/hv/run.c

                core/x86_64/win32/hv/map.h
                core/x86_64/win32/hv/map.c

                core/x86_64/win32/hv/map/dev.h
                core/x86_64/win32/hv/map/dev.c

                core/x86_64/win32/hv/map/mem.h
                core/x86_64/win32/hv/map/mem.c
        )
    endif()
elseif (UNIX AND NOT APPLE)
    if   (PRESET_LINUX_KVM)
        add_library (vapor-core STATIC
                core/cpu.h
                core/map.h
                core/sys.h
                core/mmu.h

                core/x86_64/linux/kvm/core.h
                core/x86_64/linux/kvm/core.c

                core/x86_64/linux/kvm/map.h
                core/x86_64/linux/kvm/map.c

                core/x86_64/linux/kvm/map_key.h
                core/x86_64/linux/kvm/map_key.c

                core/x86_64/linux/kvm/map/pio.h
                core/x86_64/linux/kvm/map/pio.c

                core/x86_64/linux/kvm/map/mmio.h
                core/x86_64/linux/kvm/map/mmio.c

                core/x86_64/linux/kvm/map/mem.h
                core/x86_64/linux/kvm/map/mem.c

                core/x86_64/linux/kvm/mmu.h
                core/x86_64/linux/kvm/mmu.c

                core/x86_64/linux/kvm/sys.h
                core/x86_64/linux/kvm/sys.c

                core/x86_64/linux/kvm/cpu.h
                core/x86_64/linux/kvm/cpu.c

                core/x86_64/linux/kvm/cpu/reg.h
                core/x86_64/linux/kvm/cpu/reg.c

                core/x86_64/linux/kvm/cpu/sreg.h
                core/x86_64/linux/kvm/cpu/sreg.c

                core/x86_64/linux/kvm/run.h
                core/x86_64/linux/kvm/run.c

                core/x86_64/linux/kvm/run/mmio.h
                core/x86_64/linux/kvm/run/mmio.c

                core/x86_64/linux/kvm/run/pio.h
                core/x86_64/linux/kvm/run/pio.c

                core/x86_64/linux/kvm/run/halt.h
                core/x86_64/linux/kvm/run/halt.c

        )

        target_link_libraries(vapor-core build build-arch build-arch-asm)
    endif()
endif()