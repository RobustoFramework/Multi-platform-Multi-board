# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE test_sources ${CMAKE_SOURCE_DIR}/*.c)

idf_component_register(
    SRCS ${test_sources}
    REQUIRES robusto-common
)
