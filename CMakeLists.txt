cmake_minimum_required(VERSION 3.27)

project(filesystem)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
)

if(ENABLE_CODE_COVERAGE)
    set(BUILD_TESTS TRUE)

    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

    include(CodeCoverage)

    append_coverage_compiler_flags()

    set(GCOVR_ADDITIONAL_ARGS "--exclude-throw-branches")

    setup_target_for_coverage_gcovr_html(
        NAME unit_tests_coverage
        EXECUTABLE unit_tests
        DEPENDENCIES unit_tests
        EXCLUDE "tests/*"
        EXCLUDE "examples/*"
    )
endif()

add_subdirectory(filesystem)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
