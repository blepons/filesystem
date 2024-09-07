add_subdirectory(path)

add_library(filesystem filesystem.hpp filesystem.cpp)

target_link_libraries(filesystem path)

target_include_directories(filesystem INTERFACE .)
