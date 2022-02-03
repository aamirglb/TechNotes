cmake_minimum_required(VERSION 3.1.0)
project(ftp_client VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "For MinGW use: cmake -G\"MinGW Makefiles\" -H. -Bb")
message(STATUS "For Visual Studio use: cmake -G\"Visual Studio 15 2017\" -H. -Bvc")
message(STATUS "For building using cmake use: cmake --build <build-dir>")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(ftp_client
    main.cpp
)

target_link_libraries(ftp_client Qt5::Widgets Qt5::Network Qt5::Ftp)