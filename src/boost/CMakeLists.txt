cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(boost-examples LANGUAGES CXX)

set (POCO_INC_DIR "c:/sw/poco/Foundation/include")
set (BOOST_INC_PATH "c:/sw/boost_1_81_0")
set (FMT_INC_DIR "c:/sw/fmt-9.1.0/include/")
set (BOOST_LIBRARIES "c:/sw/boost_1_81_0/lib64-msvc-14.3")

add_compile_options( /std:c++17 /await )

# fmt library 
set (FMT_LIB_DIR "c:/sw/fmt-9.1.0/lib/msvc/")
set (BOOST_LIB_DIR "c:/sw/boost_1_81_0/lib64-msvc-14.3")
set (POCO_LIB_DIR "C:/sw/poco/lib/msvc")

list(APPEND LIBS fmtd)
list(APPEND BOOST_LIBS boost_system-vc143-mt-x64-1_81 boost_coroutine-vc143-mt-x64-1_81 boost_thread-vc143-mt-x64-1_81)

include_directories(${POCO_INC_DIR})
include_directories(${BOOST_INC_PATH})
include_directories(${FMT_INC_DIR})

link_directories(${FMT_LIB_DIR})
link_directories(${BOOST_LIB_DIR})
link_directories(${POCO_LIB_DIR})

add_executable(signal_1 signal_1.cpp)
add_executable(signal_2 signal_2.cpp)
add_executable(signal_arg signal_arg.cpp)
add_executable(signal_ret signal_ret.cpp)
add_executable(str_algo1 str_algo1.cpp)
add_executable(split_string split_string.cpp)
add_executable(format format.cpp)
add_executable(options options.cpp)
add_executable(md5csum md5csum.cpp)

add_executable(sock_test sock_test.cpp)

target_link_libraries(str_algo1 ${LIBS})
target_link_libraries(split_string ${LIBS})
target_link_libraries(format ${LIBS}) 
target_link_libraries(options ${LIBS} )
target_link_libraries(md5csum ${LIBS} PocoFoundationd)
target_link_libraries(sock_test ${LIBS} ${BOOST_LIBS})


# cmake_minimum_required(VERSION 3.15)

# project(Intensity VERSION 1.0)

# set(CMAKE_CXX_COMPILER clang)

# set(BOOST_ROOT "/Users/nabiel.kandiel/code/thirdparty/boost_1_81_0")
# set(Boost_USE_STATIC_LIBS OFF)
# set(BOOST_USE_MULTITHREADED ON)
# set(BOOST_USE_STATIC_RUNTIME OFF)
# find_package(Boost 1.81 REQUIRED COMPONENTS program_options)

# add_executable(intensity intensity.cpp)
# target_link_libraries(intensity Boost::program_options)