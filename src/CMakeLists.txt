add_library(vapor STATIC
    ../include/vp/core/root.h
    ../include/vp/core/node.h
    ../include/vp/core/map.h

    ../include/vp/core/cpu.h
    ../include/vp/core/run/halt.h
    ../include/vp/core/run/mmio.h
    ../include/vp/core/run/pio.h

    ../include/vp/arch/x86_64/core/reg.h
    ../include/vp/arch/x86_64/core/sreg.h
    ../include/vp/arch/x86_64/core/port.h
    ../include/vp/arch/x86_64.h

    ../include/vp/core.h
    ../include/vp/arch.h
    ../include/vp/vp.h
)

set_target_properties(vapor PROPERTIES LINKER_LANGUAGE C)

if   (WIN32)
    if   (PRESET_WIN32_HYPERV)
        add_library (vapor-core STATIC
            core/cpu.h
            core/map.h
            core/sys.h
            core/mmu.h

            core/x86_64/hyperv/details/core.h
            core/x86_64/hyperv/details/core.c

            core/x86_64/hyperv/details/root.h
            core/x86_64/hyperv/details/root.c

            core/x86_64/hyperv/root.h
            core/x86_64/hyperv/root.c

            core/x86_64/hyperv/details/node.h
            core/x86_64/hyperv/details/node.c

            core/x86_64/hyperv/node.h
            core/x86_64/hyperv/node.c

            core/x86_64/hyperv/details/cpu.h
            core/x86_64/hyperv/details/cpu.c

            core/x86_64/hyperv/cpu.h
            core/x86_64/hyperv/cpu.c

            core/x86_64/hyperv/details/mmu.h
            core/x86_64/hyperv/details/mmu.c

            core/x86_64/hyperv/details/map.h
            core/x86_64/hyperv/details/map.c

            core/x86_64/hyperv/details/map_key.h
            core/x86_64/hyperv/details/map_key.c

            core/x86_64/hyperv/map.h
            core/x86_64/hyperv/map.c

            core/x86_64/hyperv/run/mmio.h
            core/x86_64/hyperv/run/mmio.c

            core/x86_64/hyperv/details/run/mmio.h
            core/x86_64/hyperv/details/run/mmio.c

            core/x86_64/hyperv/run/pio.h
            core/x86_64/hyperv/run/pio.c

            core/x86_64/hyperv/details/run/pio.h
            core/x86_64/hyperv/details/run/pio.c

            core/x86_64/hyperv/run/halt.h
            core/x86_64/hyperv/details/run/halt.h
            core/x86_64/hyperv/details/run/halt.c

            core/x86_64/hyperv/details/cpu/reg.h
            core/x86_64/hyperv/details/cpu/reg.c

            core/x86_64/hyperv/cpu/reg.h
            core/x86_64/hyperv/cpu/reg.c

            core/x86_64/hyperv/details/cpu/sreg.h
            core/x86_64/hyperv/details/cpu/sreg.c

            core/x86_64/hyperv/cpu/sreg.h
            core/x86_64/hyperv/cpu/sreg.c
        )

        target_link_libraries(vapor-core build build-arch build-arch-asm WinHvPlatform WinHvEmulation)
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