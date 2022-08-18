cmake_minimum_required(VERSION 3.12)
project(Glad "C")


add_library(${PROJECT_NAME} STATIC "src/glad.c")

target_include_directories(${PROJECT_NAME}
    PRIVATE "src"
    PUBLIC  "include"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 11
)

if (NOT WIN32)
    # On non-Windows platforms Glad requires libdl
    target_link_libraries(${PROJECT_NAME} PUBLIC -ldl)
endif()
