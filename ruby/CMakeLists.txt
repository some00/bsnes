find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)
find_package(ALSA REQUIRED)
find_package(SDL REQUIRED)
pkg_check_modules(libpulse IMPORTED_TARGET libpulse)
pkg_check_modules(libpulse-simple IMPORTED_TARGET libpulse-simple)

add_library(ruby ruby.cpp)
target_compile_definitions(ruby PRIVATE
    VIDEO_GLX
    VIDEO_GLX2
    VIDEO_XVIDEO
    VIDEO_XSHM
    AUDIO_ALSA
    AUDIO_PULSEAUDIO
    AUDIO_PULSEAUDIOSIMPLE
    INPUT_SDL
    INPUT_XLIB
)
target_link_libraries(ruby PRIVATE
    OpenGL::GLX
    X11::Xv
    ALSA::ALSA
    PkgConfig::libpulse
    PkgConfig::libpulse-simple
    X11::X11
    X11::Xrandr
    SDL::SDL
)
target_include_directories(ruby PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
