list(APPEND processors wdc65816 spc700 arm7tdmi)
set(processors ${processors} PARENT_SCOPE)
add_library(sfc
    interface/interface.cpp
    system/system.cpp
    controller/controller.cpp
    cartridge/cartridge.cpp
    memory/memory.cpp
    cpu/cpu.cpp
    smp/smp.cpp
    dsp/dsp.cpp
    ppu/ppu.cpp
    ppu-fast/ppu.cpp
    expansion/expansion.cpp
    coprocessor/coprocessor.cpp
    slot/slot.cpp
)
target_include_directories(sfc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(sfc PUBLIC nall co)
