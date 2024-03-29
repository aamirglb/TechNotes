project(wxWidgetExamples)
cmake_minimum_required(VERSION 3.2)

# Uncomment include directories based on need
set (FMT_INCLUDE_DIR "c:/sw/fmt-9.1.0/include/")
set (BOOST_INCLUDE_DIR "c:/sw/boost_1_81_0")
set (ASIO_INCLUDE_DIR "c:/sw/asio-1.24.0/include")
set (SPDLOG_INCLUDE_DIR "c:/sw/spdlog/include")

add_compile_definitions(_WIN32_WINNT=0x0601)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options( /std:c++20 /wd4514 /wd5219 /wd4244 /wd5045)

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

# add_executable(steady_timer steady_timer.cpp)
# add_executable(steady_timer2 steady_timer2.cpp)
# add_executable(timer timer.cpp)
# add_executable(web_client web_client.cpp)
# add_executable(time_server time_server.cpp)
# add_executable(work work.cpp)
# add_executable(poll poll.cpp)
# add_executable(work2 work2.cpp)
# add_executable(work_thread work_thread.cpp)
# add_executable(work_thread_ptr work_thread_ptr.cpp)
# add_executable(fibonacci fibonacci.cpp)
# add_executable(post_dispatch post_dispatch.cpp)
# add_executable(post_dispatch_2 post_dispatch_2.cpp)
# add_executable(strand strand.cpp)
# add_executable(strand2 strand2.cpp)
# add_executable(exception exception.cpp)
# add_executable(error_var error_var.cpp)
# add_executable(deadline_timer deadline_timer.cpp)
add_executable(recurring_timer recurring_timer.cpp)
# add_executable(recurring_timer_2 recurring_timer_2.cpp)
add_executable(beast beast.cpp)

# target_link_libraries(steady_timer ${LIBS})
# target_link_libraries(steady_timer2 ${LIBS})
# target_link_libraries(timer ${LIBS})
# target_link_libraries(web_client ${LIBS})
# target_link_libraries(time_server ${LIBS})
# target_link_libraries(work ${LIBS})
# target_link_libraries(poll ${LIBS})
# target_link_libraries(work2 ${LIBS})
# target_link_libraries(work_thread ${LIBS})
# target_link_libraries(work_thread_ptr ${LIBS})
# target_link_libraries(fibonacci ${LIBS})
# target_link_libraries(post_dispatch ${LIBS})
# target_link_libraries(post_dispatch_2 ${LIBS})
# target_link_libraries(strand ${LIBS})
# target_link_libraries(strand2 ${LIBS})
# target_link_libraries(exception ${LIBS})
# target_link_libraries(error_var ${LIBS})
# target_link_libraries(deadline_timer ${LIBS})
target_link_libraries(recurring_timer ${LIBS})
# target_link_libraries(recurring_timer_2 ${LIBS})
target_link_libraries(beast ${LIBS})