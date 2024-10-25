cmake_minimum_required(VERSION 3.12)
project(point-sphere VERSION 0.1.1)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} 
    src/main.cpp 
    include/glad.c
)

target_link_libraries(${PROJECT_NAME}
    glfw
    OpenGL::GL
)

target_include_directories(${PROJECT_NAME} PRIVATE ./include)