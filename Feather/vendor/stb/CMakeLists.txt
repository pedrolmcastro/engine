cmake_minimum_required(VERSION 3.12)
project(stb "CXX")


add_library(${PROJECT_NAME} STATIC "src/stb_image.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE
    PRIVATE "src"
    PUBLIC  "include"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
)
