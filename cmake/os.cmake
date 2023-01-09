if (WIN32)
    # windows

    if (OPT_WARNS_AS_ERR)
        set_target_properties(
            GLPlaces
            PROPERTIES 
                LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS"
        )
    endif()
endif()
