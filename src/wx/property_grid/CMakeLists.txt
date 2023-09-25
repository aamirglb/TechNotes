cmake_minimum_required(VERSION 3.20)
project(property_grid_example)

set(wxWidgets_ROOT_DIR "C:/Users/aamir.ali/Documents/playground/Programs/libraries/wx321")
set(wxWidgets_LIB_DIR "C:/Users/aamir.ali/Documents/playground/Programs/libraries/wx321/lib/vc_x64_lib")
set(wxWidgets_CONFIGURATION "mswd")

find_package(wxWidgets REQUIRED gl core base propgrid OPTIONAL_COMPONENTS net)
# find_package( wxWidgets 3.2.1 REQUIRED )
include(${wxWidgets_USE_FILE})

add_executable(main WIN32 main.cpp)
target_link_libraries(main ${wxWidgets_LIBRARIES})
