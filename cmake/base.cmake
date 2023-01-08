add_library(
    base
    INTERFACE
)

include(cmake/base/compilers.cmake)
include(cmake/base/warnings.cmake)
include(cmake/base/optimizations.cmake)

target_link_libraries(
    GLPlaces
    PRIVATE
        base
)
