if (WIN32)
    # windows

    target_include_directories(
        GLPlaces
        PRIVATE
            lib/glfw/include
    )

    target_link_directories(
        GLPlaces
        PRIVATE
            lib/glfw/lib-vc2019
    )

    target_link_libraries(
        GLPlaces
        PRIVATE
            glfw3.lib
    )
else()
    # linux

    find_package(glfw3 REQUIRED)
    target_link_libraries(
        GLPlaces
        PUBLIC
            glfw
    )
endif()
