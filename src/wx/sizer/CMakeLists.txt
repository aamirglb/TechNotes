cmake_minimum_required(VERSION 3.20)
project(sizer)

set(wxWidgets_ROOT_DIR "C:/Users/aamir.ali/Documents/playground/Programs/libraries/wx321")
set(wxWidgets_LIB_DIR "C:/Users/aamir.ali/Documents/playground/Programs/libraries/wx321/lib/vc_x64_lib")
set(wxWidgets_CONFIGURATION "mswd")
# set(wxWidgets_LIBRARIES )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

if(wxWidgets_FOUND)
    message(STATUS "wxWidget FOUND!!")
    message(STATUS "wxWidget Libraries: ${wxWidgets_LIBRARIES}")
endif()

add_executable(sizer WIN32 main2.cpp)
target_link_libraries(sizer PRIVATE ${wxWidgets_LIBRARIES})

add_executable(main WIN32 main.cpp)
target_link_libraries(main PRIVATE ${wxWidgets_LIBRARIES})
# target_link_libraries(hello PRIVATE wx::net wx::core wx::base)