cmake_minimum_required(VERSION 3.21)
PROJECT(gl_places CXX)

include(opts.cmake)

add_executable(GLPlaces)

target_sources(
    GLPlaces
    PRIVATE
        src/main.cc
        src/app.cc
        src/world.cc
        src/util/gl_info.cc
        src/util/fs.cc
        src/object/shaders.cc
        src/scene/museum.cc
)

target_include_directories(
    GLPlaces
    PRIVATE
        header
)

target_compile_features(
    GLPlaces
    PUBLIC
        cxx_std_17
)

include(cmake/base.cmake)
include(cmake/libs.cmake)
include(cmake/os.cmake)
include(cmake/debug.cmake)
include(cmake/release.cmake)
