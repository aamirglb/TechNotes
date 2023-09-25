cmake_minimum_required(VERSION 3.20)
project(burning_app)

set(wxWidgets_ROOT_DIR "C:/Users/aamir.ali/Documents/playground/Programs/libraries/wx321")
set(wxWidgets_LIB_DIR "C:/Users/aamir.ali/Documents/playground/Programs/libraries/wx321/lib/vc_x64_lib")
set(wxWidgets_CONFIGURATION "mswd")

find_package(wxWidgets REQUIRED gl core base propgrid OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

add_executable(burning_app WIN32 main.cpp burning.cpp widget.cpp)
target_link_libraries(burning_app ${wxWidgets_LIBRARIES})
