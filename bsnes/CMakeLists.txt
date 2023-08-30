add_library(bsnes_common
    emulator/emulator.cpp
    filter/filter.cpp
    lzma/lzma.cpp
)
target_include_directories(bsnes_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(bsnes_common PRIVATE co)

add_subdirectory(sfc)
add_subdirectory(gb)
add_subdirectory(processor)

add_subdirectory(target-bsnes)
add_subdirectory(target-libretro)
