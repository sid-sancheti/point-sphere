cmake_minimum_required(VERSION 3.12)
project(point-sphere VERSION 0.1.1)

find_package(OpenGL REQUIRED)

add_executable(point-sphere 
    src/main.cpp 
    src/glad.c
)

target_link_libraries(point-sphere 
    glfw
    OpenGL::GL
)