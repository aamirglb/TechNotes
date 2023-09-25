project(exploring-c++20)
cmake_minimum_required(VERSION 3.2)

# Uncomment include directories based on need
set (FMT_INCLUDE_DIR "c:/sw/fmt-9.1.0/include/")
set (BOOST_INCLUDE_DIR "c:/sw/boost_1_81_0")
set (ASIO_INCLUDE_DIR "c:/sw/asio-1.24.0/include")
set (SPDLOG_INCLUDE_DIR "c:/sw/spdlog/include")
set (CXX_STANDARD 20)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options( /std:c++20 -interface /wd4514 /wd5219 /wd4244 /wd5045)

    # fmt library 
    set (FMT_LIB_DIR "c:/sw/fmt-9.1.0/lib/msvc/")
    list(APPEND LIBS fmtd)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -std=c++20)

    # fmt library
    set (FMT_LIB_DIR "c:/sw/fmt-9.1.0/lib/mingw")
    set (SPDLOG_LIB_DIR "c:/sw/spdlog/lib/msvc")
    list(APPEND LIBS fmt )
endif()

include_directories(${FMT_INCLUDE_DIR})
include_directories(${BOOST_INCLUDE_DIR})
include_directories(${ASIO_INCLUDE_DIR})
include_directories(${SPDLOG_INCLUDE_DIR})

link_directories(${FMT_LIB_DIR})
link_directories(${SPDLOG_LIB_DIR})

# add_executable(list0101 list0101.cpp)
add_executable(generic_add generic_add.cpp)

target_link_libraries(generic_add ${LIBS})
