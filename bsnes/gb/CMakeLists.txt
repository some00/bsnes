add_library(gb
    Core/apu.c
    Core/camera.c
    Core/rumble.c
    Core/display.c
    Core/gb.c
    Core/joypad.c
    Core/mbc.c
    Core/memory.c
    Core/printer.c
    Core/random.c
    Core/rewind.c
    Core/save_state.c
    Core/sgb.c
    Core/sm83_cpu.c
    Core/symbol_hash.c
    Core/timing.c
)
target_compile_definitions(gb PRIVATE
    -DGB_INTERNAL
    -DGB_DISABLE_DEBUGGER
    -DGB_DISABLE_CHEATS
    -D_GNU_SOURCE
    -DGB_VERSION=\"0.14.7\"
)
target_compile_options(gb PRIVATE -Wno-multichar)
