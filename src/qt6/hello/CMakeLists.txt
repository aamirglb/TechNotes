cmake_minimum_required(VERSION 3.25)
project(Simple_GUI)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS " /Zc:__cplusplus  /permissive-")

#=============== INCLUSION OF Qt ================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# set(CMAKE_PREFIX_PATH "C:\\Qt\\6.5.2\\mingw_64\\lib\\cmake")

find_package(Qt6Core REQUIRED ) #find needed packages
find_package(Qt6Widgets REQUIRED )

#=========== ADDING EXECUTABLE AND LINKING LIBRARIES ============#
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

# cmake_minimum_required(VERSION 3.16)

# project(helloworld VERSION 1.0.0 LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS " /Zc:__cplusplus  /permissive-")

# find_package(Qt6 REQUIRED COMPONENTS Core)
# qt_standard_project_setup()

# qt_add_executable(helloworld
#     main.cpp
# )

# target_link_libraries(helloworld PRIVATE Qt6::Core)