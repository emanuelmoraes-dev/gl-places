add_library(
    debug_env
    INTERFACE
)

target_include_directories(
    debug_env
    INTERFACE
        env/debug
)

target_link_libraries(
    GLPlaces
    PRIVATE
        debug debug_env
)
