set(cpp ${CMAKE_CURRENT_BINARY_DIR}/resource.cpp)
set(hdr ${CMAKE_CURRENT_BINARY_DIR}/resource.hpp)
add_custom_command(OUTPUT ${cpp} ${hdr}
    COMMAND $<TARGET_FILE:sourcery> "${CMAKE_CURRENT_SOURCE_DIR}/resource/resource.bml" "${cpp}" "${hdr}"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resource
)

add_executable(bsnes
    bsnes.cpp
    program/program.cpp
    input/input.cpp
    presentation/presentation.cpp
    settings/settings.cpp
    tools/tools.cpp
    ${cpp}
)
target_link_libraries(bsnes PRIVATE
    hiro
    ruby
    bsnes_common
    sfc
    processors
)
