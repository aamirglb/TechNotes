cmake_minimum_required(VERSION 3.1.0)
project(spreadsheet VERSION 1.0.0 LANGUAGES CXX)

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
            mainwindow.cpp
            finddialog.cpp
            gotocelldialog.cpp
            sortdialog.cpp
            spreadsheet.cpp
            cell.cpp
            spreadsheet.qrc)

#qt5_add_resources(SOURCES spreadsheet.qrc)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(spreadsheet
    ${SOURCES}
)

target_link_libraries(spreadsheet Qt5::Widgets)