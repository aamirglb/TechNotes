cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(learnopengl)

add_compile_definitions(GLEW_STATIC)
add_compile_options( /std:c++20 )

# specify include directory
set (GLFW_INC_DIR "c:/sw/glfw-3.3.8/include")
set (GLAD_INC_DIR "c:/sw/glad/include")

set (GLFW_LIB_DIR "c:/sw/glfw-3.3.8/x64/lib-vc2022")
list(APPEND LIBRARIES glfw3 opengl32)

include_directories(${GLFW_INC_DIR})
include_directories(${GLAD_INC_DIR})

link_directories(${GLFW_LIB_DIR})

add_executable(hello hello.cpp glad.c)

target_link_libraries(hello ${LIBRARIES})
