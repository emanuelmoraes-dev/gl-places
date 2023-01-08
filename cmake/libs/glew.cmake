if (WIN32)
    # windows

    target_include_directories(
        GLPlaces
        PRIVATE
            lib/glew/include
    )

    target_link_directories(
        GLPlaces
        PRIVATE
            lib/glew/lib/Release/x64
    )

    target_link_libraries(
        GLPlaces
        PRIVATE
            glew32.lib
    )
else()
    # linux

    find_package(GLEW REQUIRED)
    target_link_libraries(
        GLPlaces
        PRIVATE
            GLEW::glew
    )
endif()
