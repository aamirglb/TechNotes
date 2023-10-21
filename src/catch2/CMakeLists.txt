project(catch2-programs)
cmake_minimum_required(VERSION 3.2)

# Uncomment include directories based on need
set (CATCH2_INCLUDE_DIR "c:/sw/catch2/include/")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/std:c++20 /wd4514 /wd5219 /wd4244 /wd5045)

    # catch2 library 
    set (CATCH2_LIB_DIR "c:/sw/catch2/lib/msvc/")
    list(APPEND LIBS Catch2Maind Catch2d)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -std=c++20)

    # catch2 library
    set (CATCH2_LIB_DIR "c:/sw/catch2/lib/mingw")
    list(APPEND LIBS Catch2Main Catch2)
endif()

include_directories(${CATCH2_EXTRA_INC} ${CATCH2_INCLUDE_DIR})
link_directories(${CATCH2_LIB_DIR})

add_executable(getitem getitem.cpp)

target_link_libraries(getitem ${LIBS})
