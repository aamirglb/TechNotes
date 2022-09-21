# Minimum required version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Project name and suppported language
project(ping-pong LANGUAGES CXX)

set (RAYLIB_INCLUDE_DIRS "d:/SW/raylib/include/")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options( /std:c++17 /wd4514 /wd5219 /wd4244 /wd5045)
    set (RAYLIB_LIB_DIRS "d:/SW/raylib/lib/msvc-22/")
else()
    add_compile_options(-Wall -Wextra -Wpedantic -std=c++17)
    set (RAYLIB_LIB_DIRS "d:/SW/raylib/lib/mingw")
    # list(APPEND RAYLIB_LIBS raylib winmm)
endif()

if(WIN32)
    list(APPEND RAYLIB_LIBS raylib winmm)
    include_directories(${RAYLIB_INCLUDE_DIRS})
    link_directories(${RAYLIB_LIB_DIRS})
else()
endif()

add_executable(ping-pong main.cpp)
target_link_libraries(ping-pong ${RAYLIB_LIBS})

