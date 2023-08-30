add_library(co
    amd64.c
    ucontext.c
    libco.c
)
target_include_directories(co PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
