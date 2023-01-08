if (WIN32)
    # windows

    target_link_libraries(
        GLPlaces
        PRIVATE
            opengl32.lib
    )
else()
    # linux

    find_package(OpenGL REQUIRED)
    target_link_libraries(
        GLPlaces
        PRIVATE
            OpenGL::OpenGL
    )
endif()
