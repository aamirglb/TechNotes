project(wxWidgetExamples)
cmake_minimum_required(VERSION 3.2)

# Uncomment include directories based on need
set (FMT_INCLUDE_DIR "c:/sw/fmt-9.1.0/include/")
set (BOOST_INCLUDE_DIR "c:/sw/boost_1_81_0")
set (ASIO_INCLUDE_DIR "c:/sw/asio-1.24.0/include")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options( /std:c++20 /wd4514 /wd5219 /wd4244 /wd5045)

    # fmt library 
    set (FMT_LIB_DIR "c:/sw/fmt-9.1.0/lib/msvc/")
    list(APPEND LIBS fmtd)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -std=c++20)

    # fmt library
    set (FMT_LIB_DIR "c:/sw/fmt-9.1.0/lib/mingw")
    list(APPEND LIBS fmt)
endif()

include_directories(${FMT_INCLUDE_DIR})
include_directories(${BOOST_INCLUDE_DIR})
include_directories(${ASIO_INCLUDE_DIR})

link_directories(${FMT_LIB_DIR})

add_executable(deadline_timer deadline_timer.cpp)
add_executable(post_work post_work.cpp)
add_executable(strand strand.cpp)
add_executable(echo_server2 echo_server2.cpp)
add_executable(tcp_echo_server tcp_echo_server.cpp)
add_executable(tcp_chat_server tcp_chat_server.cpp)

target_link_libraries(deadline_timer ${LIBS})
target_link_libraries(post_work ${LIBS})
target_link_libraries(strand ${LIBS})
target_link_libraries(echo_server2 ${LIBS})
target_link_libraries(tcp_echo_server ${LIBS})
target_link_libraries(tcp_chat_server ${LIBS})