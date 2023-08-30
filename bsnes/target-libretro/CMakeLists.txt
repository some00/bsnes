add_library(bsnes-libretro SHARED libretro.cpp)
target_compile_options(bsnes-libretro PRIVATE
    -Wl,--no-undefined
    -Wl,--version-script=link.T
    -lgomp -Wl,-Bdynamic )
target_link_libraries(bsnes-libretro PRIVATE
    bsnes_common
    co
    sfc
    processors
)
