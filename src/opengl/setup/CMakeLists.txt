cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(opengl-setup LANGUAGES CXX)

add_compile_definitions(GLEW_STATIC)
add_compile_options( /std:c++17 )

# specify include directory
set (GLFW_INC_DIR "c:/sw/glfw-3.3.8/include")
set (GLEW_INC_DIR "c:/sw/glew-2.1.0/include")
set (GLUT_INC_DIR "c:/sw/freeglut/include")

# specify library directory
set (GLFW_LIB_DIR "c:/sw/glfw-3.3.8/x64/lib-vc2022")
set (GLEW_LIB_DIR "c:/sw/glew-2.1.0/lib/Release/x64")
set (GLUT_LIB_DIR "c:/sw/freeglut/lib/msvc")

list(APPEND LIBRARIES glfw3 opengl32 glew32s)
list(APPEND GLUT_LIBRARIY glu32 freeglutd freeglut_staticd)

include_directories(${GLFW_INC_DIR})
include_directories(${GLEW_INC_DIR})
include_directories(${GLUT_INC_DIR})

link_directories(${GLFW_LIB_DIR})
link_directories(${GLEW_LIB_DIR})
link_directories(${GLUT_LIB_DIR})

add_executable(main main.cpp)
add_executable(vertex_buffer vertex_buffer.cpp)
add_executable(vertex_buffer2 vertex_buffer2.cpp)
add_executable(index_buffer index_buffer.cpp)
add_executable(glfw_intro glfw_intro.cpp)
add_executable(error_handling error_handling.cpp)
add_executable(uniform uniform.cpp)

# programs using freeglut
add_executable(cube cube.cpp)
add_executable(glut_intro glut_intro.cpp)

target_link_libraries(main ${LIBRARIES})
target_link_libraries(vertex_buffer ${LIBRARIES})
target_link_libraries(vertex_buffer2 ${LIBRARIES})
target_link_libraries(index_buffer ${LIBRARIES})
target_link_libraries(glfw_intro ${LIBRARIES})
target_link_libraries(error_handling ${LIBRARIES})
target_link_libraries(uniform ${LIBRARIES})

# programs using freeglut
target_link_libraries(cube ${LIBRARIES} ${GLUT_LIBRARIY})
target_link_libraries(glut_intro ${LIBRARIES} ${GLUT_LIBRARIY})
