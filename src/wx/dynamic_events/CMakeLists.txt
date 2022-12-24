cmake_minimum_required(VERSION 3.20)
project(hello)

set(wxWidgets_ROOT_DIR "C:/Users/aamir.ali/Documents/playground/Programs/libraries/wx321")
set(wxWidgets_LIB_DIR "C:/Users/aamir.ali/Documents/playground/Programs/libraries/wx321/lib/vc_x64_lib")
set(wxWidgets_CONFIGURATION "mswd")
# set(wxWidgets_LIBRARIES )

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

if(wxWidgets_FOUND)
    message(STATUS "wxWidget FOUND!!")
    message(STATUS "wxWidget Libraries: ${wxWidgets_LIBRARIES}")
endif()

add_executable(hello WIN32 app.cpp)
target_link_libraries(hello PRIVATE ${wxWidgets_LIBRARIES})
# target_link_libraries(hello PRIVATE wx::net wx::core wx::base)