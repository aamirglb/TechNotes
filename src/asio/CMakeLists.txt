cmake_minimum_required(VERSION 3.2)
project(ThinkAsync)

if (WIN32)
    set(ASIO_INCLUDE_DIR "c:/sw/asio-1.30.2/include")
    list(APPEND WIN_SOCK_LIBS ws2_32 wsock32)
else()
    set(ASIO_INCLUDE_DIR "~/asio-1.30.2/include")
endif()

add_compile_definitions(_WIN32_WINNT=0x0601)


if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/std:c++20 /wd4514)
else()
    add_compile_options(-std=c++20 -Wall -Wextra -Wpedantic)
endif()

include_directories(${ASIO_INCLUDE_DIR})

add_executable(server server.cpp)
add_executable(client client.cpp)

add_executable(poll poll.cpp)
add_executable(work work.cpp)

add_executable(multi_timer multi_timer.cpp)
add_executable(multi_thread multi_thread.cpp)
add_executable(multi_thread-v2 multi_thread-v2.cpp)
add_executable(fib fib.cpp)

add_executable(post_dispatch post_dispatch.cpp)

target_link_libraries(server ${WIN_SOCK_LIBS})
target_link_libraries(client ${WIN_SOCK_LIBS})

target_link_libraries(poll ${WIN_SOCK_LIBS})
target_link_libraries(work ${WIN_SOCK_LIBS})

target_link_libraries(multi_timer ${WIN_SOCK_LIBS})
target_link_libraries(multi_thread ${WIN_SOCK_LIBS})
target_link_libraries(multi_thread-v2 ${WIN_SOCK_LIBS})
target_link_libraries(fib ${WIN_SOCK_LIBS})

target_link_libraries(post_dispatch ${WIN_SOCK_LIBS})
