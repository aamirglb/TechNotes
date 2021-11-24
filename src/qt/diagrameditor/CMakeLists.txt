cmake_minimum_required(VERSION 3.1.0)
project(diagrameditor VERSION 1.0.0 LANGUAGES CXX)

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
            window.cpp
            node.cpp
            link.cpp
            resources.qrc)

#qt5_add_resources(SOURCES diagrameditor.qrc)
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

add_executable(diagrameditor
    ${SOURCES}
)

target_link_libraries(diagrameditor Qt5::Widgets Qt5::Core)