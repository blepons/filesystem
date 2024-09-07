find_package(Catch2 3 REQUIRED)

add_executable(
    unit_tests
    path_testing.cpp
    filesystem_testing.cpp
)

target_link_libraries(
    unit_tests
    PRIVATE path
    PRIVATE filesystem
    PRIVATE Catch2::Catch2WithMain
)

set_source_files_properties(
    path_testing.cpp
    filesystem_testing.cpp
    PROPERTIES
    SKIP_LINTING ON
)
