cmake_minimum_required(VERSION 3.20)
project(events)

set(wxWidgets_ROOT_DIR "C:/Users/aamir.ali/Documents/playground/Programs/libraries/wx321")
set(wxWidgets_LIB_DIR "C:/Users/aamir.ali/Documents/playground/Programs/libraries/wx321/lib/vc_x64_lib")
set(wxWidgets_CONFIGURATION "mswd")

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})
# add_definitions(wx-config --libs std,richtext)

add_executable(main WIN32 app.cpp frame.cpp editor.cpp canvas.cpp)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE ${wxWidgets_LIBRARIES})