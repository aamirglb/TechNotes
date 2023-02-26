# Minimum required version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Project name and suppported language
project(maze_generator LANGUAGES CXX)

# Enable C++17 support
add_compile_options( /std:c++17 /wd4514 /wd5219 /wd4244 /wd5045)

if(WIN32)
    # list(APPEND CMAKE_MODULE_PATH "D:/sw/SFML/cmake")
    include_directories("c:/sw/SFML/include")
    link_directories("c:/sw/SFML/lib/msvc")
else()
    # SFML library
    find_package(SFML REQUIRED graphics window system network audio)
    include_directories(${SFML_INCLUDE_DIR})
endif()

add_executable(maze_generator main.cpp settings.cpp cell.cpp maze.cpp)
add_executable(so_shader so_shader.cpp)

target_link_libraries(maze_generator sfml-graphics-d sfml-window-d sfml-system-d ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(so_shader sfml-graphics-d sfml-window-d sfml-system-d ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

# cl /std:c++17 /I c:/sw/SFML/include so_shader.cpp /link /LIBPATH:"c:/sw/SFML/lib/msvc" sfml-graphics-d sfml-window-d sfml-system-d