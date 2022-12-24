cmake_minimum_required(VERSION 3.20)
project(list)

set(wxWidgets_ROOT_DIR "C:/Users/aamir.ali/Documents/playground/Programs/libraries/wx321")
set(wxWidgets_LIB_DIR "C:/Users/aamir.ali/Documents/playground/Programs/libraries/wx321/lib/vc_x64_lib")
set(wxWidgets_CONFIGURATION "mswd")
# set(wxWidgets_LIBRARIES )

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

add_executable(list WIN32 app.cpp)
target_link_libraries(list PRIVATE ${wxWidgets_LIBRARIES})
