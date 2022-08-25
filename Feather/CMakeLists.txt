cmake_minimum_required(VERSION 3.12)
project(Feather "CXX")


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("vendor/Glad")
add_subdirectory("vendor/GLFW")
add_subdirectory("vendor/stb")


file(GLOB_RECURSE sources "src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${sources})

target_include_directories(${PROJECT_NAME}
    PUBLIC  "include"
    PRIVATE "vendor/stb/include"
    PRIVATE "vendor/GLFW/include"
    PRIVATE "vendor/Glad/include"
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC Glad
    PUBLIC glfw
    PUBLIC stb
    PUBLIC m
)

target_precompile_headers(${PROJECT_NAME}
    PRIVATE "include/Precompiled.hpp"
)

set_target_properties(Feather PROPERTIES
    CXX_STANDARD 20
)


if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Define Debug Flags
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC LOGGING ASSERTING)
endif()


# Add Compiler Warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Werror -pedantic)
endif()
