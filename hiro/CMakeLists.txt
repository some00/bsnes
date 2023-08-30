pkg_check_modules(gtk3 IMPORTED_TARGET gtk+-3.0)

set(cpp ${CMAKE_CURRENT_BINARY_DIR}/resource.cpp)
set(hdr ${CMAKE_CURRENT_BINARY_DIR}/resource.hpp)
add_custom_command(OUTPUT ${cpp} ${hdr}
    COMMAND $<TARGET_FILE:sourcery> "${CMAKE_CURRENT_SOURCE_DIR}/resource/resource.bml" "${cpp}" "${hdr}"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resource
)


add_library(hiro hiro.cpp ${cpp})
target_compile_definitions(hiro PRIVATE -DHIRO_GTK=3)
target_link_libraries(hiro PRIVATE
    PkgConfig::gtk3
    nall
)
