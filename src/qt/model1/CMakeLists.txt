cmake_minimum_required(VERSION 3.1.0)
project(model1 VERSION 1.0.0 LANGUAGES CXX)

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
            qml.qrc)

#qt5_add_resources(SOURCES model1.qrc)
find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)

add_executable(model1
    ${SOURCES}
)

target_link_libraries(model1 
                    Qt5::Widgets
                    Qt5::Qml
                    Qt5::Quick
                    )
