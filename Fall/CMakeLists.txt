cmake_minimum_required(VERSION 3.12)
project(Fall "CXX")


add_subdirectory("../Feather" "Feather")


file(GLOB_RECURSE sources "src/*.cpp")
add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME}
    PRIVATE Feather
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX ".out"
    CXX_STANDARD 20
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
