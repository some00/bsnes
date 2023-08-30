cmake_minimum_required(VERSION 3.27)
project(bsnes)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
find_package(PkgConfig REQUIRED)

add_subdirectory(libco)
add_subdirectory(nall)
add_subdirectory(ruby)
add_subdirectory(sourcery)
add_subdirectory(hiro)
add_subdirectory(bsnes)
