project(mine_sweeper)
cmake_minimum_required(VERSION 3.2)
aux_source_directory(. SRC_LIST)

# set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(mine_sweeper cApp.cpp cMain.cpp)
target_link_libraries(mine_sweeper ${wxWidgets_LIBRARIES})
