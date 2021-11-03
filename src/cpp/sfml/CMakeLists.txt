# Minimum required version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Project name and suppported language
project(sfml_test LANGUAGES CXX)

# Enable C++17 support
add_compile_options(-std=c++17)

# SFML library
find_package(SFML REQUIRED graphics window system network audio)

include_directories(${SFML_INCLUDE_DIR})

add_executable(sfml_test 1.cpp) 
target_link_libraries(sfml_test m sfml-graphics sfml-window sfml-system ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
