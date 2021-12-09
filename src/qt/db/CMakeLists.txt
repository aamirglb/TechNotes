cmake_minimum_required(VERSION 3.1.0)
project(db VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "Generating Build Files")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()
set(SOURCES main.cpp 
            resources.qrc)

#qt5_add_resources(SOURCES spreadsheet.qrc)
find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)

add_executable(db
    ${SOURCES}
)

target_link_libraries(db Qt5::Widgets Qt5::Sql)