cmake_minimum_required(VERSION 3.21)
PROJECT(gl_places CXX)

include(opts.cmake)

add_executable(GLPlaces)

target_sources(
    GLPlaces
    PRIVATE
        src/main.cc
        src/fs.cc
        src/info.cc
)

target_include_directories(
    GLPlaces
    PRIVATE
        src/headers
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
