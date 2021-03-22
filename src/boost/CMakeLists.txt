cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(boost-examples LANGUAGES CXX)

set(BOOST_INC_PATH "/usr/include/")
add_executable(signal_1 signal_1.cpp)
add_executable(signal_2 signal_2.cpp)
add_executable(signal_arg signal_arg.cpp)
add_executable(signal_ret signal_ret.cpp)

target_include_directories(signal_1 PRIVATE ${BOOST_INC_PATH})
target_include_directories(signal_2 PRIVATE ${BOOST_INC_PATH})
target_include_directories(signal_arg PRIVATE ${BOOST_INC_PATH})
target_include_directories(signal_ret PRIVATE ${BOOST_INC_PATH})