cmake_minimum_required(VERSION 4.0.0)
project(opengl_renderer VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)
list(APPEND CMAKE_PREFIX_PATH "C:/Users/clair/Desktop/vcpkg/installed/x64-windows")

find_package(glad REQUIRED)     # 0.1.36 
find_package(glfw3 REQUIRED)    # 3.3 
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(
    opengl_renderer
    src/config.h
    src/config.cpp
    src/main.cpp 
    # src/glad.c
    src/model/camera.cpp
    src/model/cube.cpp
    src/model/scene.cpp
    src/view/cube_mesh.cpp
    src/view/material.cpp
    src/view/renderer.cpp
    src/view/shader.cpp
    src/controller/app.cpp
    )

target_link_libraries(
    opengl_renderer
    glfw # lets us use GLFW functions
    glad
    )

target_include_directories(opengl_renderer PRIVATE "C:/Users/clair/Desktop/vcpkg")