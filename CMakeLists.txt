cmake_minimum_required(VERSION 3.10)
project(FOOL C)

set(CMAKE_C_STANDARD 23)

# Optionally enable static build of raylib
option(BUILD_SHARED_LIBS OFF)

# Add raylib as a subdirectory
add_subdirectory(raylib)

# Your source files
add_executable(FOOL main.c
        util/random/randomutil.c
        util/random/randomutil.h
        util/terrain/terrainutil.c
        util/terrain/terrainutil.h
        util/math/mathutil.c
        util/math/mathutil.h
        globals.h
        entity/base/base.h
        entity/base/base.c
        globals.c
)

# Link raylib (which you built from source)
target_link_libraries(FOOL raylib)

# raylib needs some system libraries depending on the platform
if (WIN32)
    target_link_libraries(FOOL winmm gdi32 opengl32)
elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(CoreVideo_LIBRARY CoreVideo)
    target_link_libraries(FOOL ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${CoreVideo_LIBRARY})
elseif(UNIX)
    target_link_libraries(FOOL m pthread dl GL X11)
endif()
