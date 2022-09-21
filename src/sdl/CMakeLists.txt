cmake_minimum_required(VERSION 3.5)
project(SDL_Test LANGUAGES CXX)

set(SDL_INCLUDE_DIRS "D:/SW/SDL2-devel-2.24.0-VC/include")
set(SDL_LIB_DIRS "D:/SW/SDL2-devel-2.24.0-VC/lib/x64")

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/std:c++20)
    list(APPEND SDL2_LIBRARIES SDL2.lib SDL2main.lib)
else()
endif()

if(WIN32)
    include_directories(${SDL_INCLUDE_DIRS})
    link_directories(${SDL_LIB_DIRS})
else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    # set(SDL2_LIBRARIES "SDL2")
endif()



# add_compile_options(-Wall -Wextra -Wpedantic -std=c++17)

# # include_directories(
# #     /usr/include/SDL2/
# # )

# set(SDL2_INCLUDE_DIRS "/usr/include/SDL2")
#

add_executable(hello_sdl hello_sdl.cpp)
add_executable(simple_win simple_window.cpp)
add_executable(image_show image_show.cpp)
add_executable(hello2 hello2.cpp)
add_executable(game game_main.cpp game.cpp)
# add_executable(sdl_setup sdl_setup.cpp)
# add_executable(game game.cpp main.cpp)


target_link_libraries(hello_sdl ${SDL2_LIBRARIES})
target_link_libraries(simple_win ${SDL2_LIBRARIES})
target_link_libraries(image_show ${SDL2_LIBRARIES})
target_link_libraries(hello2 ${SDL2_LIBRARIES})
target_link_libraries(game ${SDL2_LIBRARIES})
# target_link_libraries(sdl_setup ${SDL2_LIBRARIES})
# target_link_libraries(game ${SDL2_LIBRARIES})
