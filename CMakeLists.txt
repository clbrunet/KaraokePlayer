cmake_minimum_required(VERSION 3.18.0)
project(KaraokePlayer VERSION 1.0.0)

# ---------------------------------- CMake config

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CPM_SOURCE_CACHE "${CMAKE_CURRENT_SOURCE_DIR}/ext" CACHE STRING "")
include(cmake/CPM.cmake)

# ---------------------------------- Dependencies

# Package SDL (windowing, gl context)
set(SDL_TEST OFF)
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
CPMAddPackage("gh:libsdl-org/SDL@2.26.4#release-2.26.4")

# Package pugixml (xml parsing)
CPMAddPackage("gh:zeux/pugixml@1.13")

# Package stb (vorbis file reader)
CPMAddPackage(
    NAME stb
    GIT_REPOSITORY "https://github.com/nothings/stb.git"
    GIT_TAG "5736b15f7ea0ffb08dd38af21067c314d6a3aae9"
    DOWNLOAD_ONLY ON
)
if (stb_ADDED)
    add_library(stb INTERFACE)
    target_include_directories(stb INTERFACE "${stb_SOURCE_DIR}/stb")

    add_library(stb_vorbis INTERFACE)
    target_link_libraries(stb_vorbis INTERFACE stb)
    set_target_properties(stb_vorbis PROPERTIES VERSION 1.22)
    add_library(stb::vorbis ALIAS stb_vorbis)
endif()

# Package GLAD (gl loader)
CPMAddPackage(
    NAME glad
    GIT_REPOSITORY "https://github.com/Dav1dde/glad.git"
    VERSION "2.0.4"
    DOWNLOAD_ONLY ON
)
if (glad_ADDED)
    add_subdirectory(${glad_SOURCE_DIR}/cmake ${glad_BINARY_DIR})
    glad_add_library(glad_gl_core_33
        REPRODUCIBLE
        API gl:core=3.3
    )
    add_library(glad::glad ALIAS glad_gl_core_33)
endif()

# ---------------------------------- Main target

file(GLOB_RECURSE target_sources "src/*.cpp")
file(GLOB_RECURSE target_headers "src/*.h")
add_executable(KaraokePlayer ${target_sources} ${target_headers})
target_include_directories(KaraokePlayer PRIVATE "src")
target_link_libraries(KaraokePlayer
    SDL2::SDL2
    glad::glad
    pugixml::static
    stb::vorbis
)
