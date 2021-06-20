project(wxWidgetExamples)
cmake_minimum_required(VERSION 3.2)
aux_source_directory(. SRC_LIST)

# set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(hello hello_wx.cpp)
target_link_libraries(hello ${wxWidgets_LIBRARIES})

add_executable(hello2 hello2.cpp)
target_link_libraries(hello2 ${wxWidgets_LIBRARIES})

add_executable(event_handle event_handle.cpp)
target_link_libraries(event_handle ${wxWidgets_LIBRARIES})