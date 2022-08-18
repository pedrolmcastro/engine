cmake_minimum_required(VERSION 3.12)
project(Sandbox "CXX")


# Define Debug and Release Modes
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-O0 -g)
    add_compile_definitions(LOGGING ASSERTING)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3)
    add_compile_definitions(NDEBUG)
endif()


add_subdirectory("../Feather" "Feather")


file(GLOB_RECURSE sources "src/*.cpp")
add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME}
    PRIVATE "src"
    PRIVATE "../Feather/include"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Feather
    PRIVATE Glad
    PRIVATE glfw
    PRIVATE stb
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX ".out"
    CXX_STANDARD 20
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)


# Add Compiler Warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -pedantic)
endif()
