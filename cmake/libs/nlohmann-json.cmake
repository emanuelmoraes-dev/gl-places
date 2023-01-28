# don't run tests
# set(JSON_BuildTests OFF CACHE INTERNAL "")

# add_subdirectory(lib/nlohmann-json-3.11.2)

# target_link_libraries(
#     GLPlaces
#     PRIVATE
#         nlohmann_json::nlohmann_json
# )

target_include_directories(
    GLPlaces
    PRIVATE
        lib/nlohmann/json-3.11.2/single_include
)
