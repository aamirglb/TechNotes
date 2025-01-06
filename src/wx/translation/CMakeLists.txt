cmake_minimum_required(VERSION 3.20)
project(translation)

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

IF (WIN32)
  set(wxWidgets_ROOT_DIR "c:/sw/wx326")
  set(wxWidgets_LIB_DIR "c:/sw/wx326/lib/vc_x64_lib")
ENDIF()

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})
file(GLOB sources src/*.cpp)

add_executable(translation WIN32 ${sources})

if(wxWidgets_FOUND)
    target_link_libraries(translation ${wxWidgets_LIBRARIES})
    target_include_directories(translation PRIVATE ${wxWidgets_INCLUDE_DIRS})
    message(STATUS "Found wxWidgets ${wxWidgets_VERSION_STRING}")
else()
    message(STATUS "wxWidgets Not Found")
endif()
