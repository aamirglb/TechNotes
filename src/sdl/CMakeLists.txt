cmake_minimum_required(VERSION 3.0.2)
project(SDL_Test)

find_package(SDL2 REQUIRED)

add_compile_options(-Wall -Wextra -Wpedantic -std=c++17)

# include_directories(
#     /usr/include/SDL2/
# )

set(SDL2_INCLUDE_DIRS "/usr/include/SDL2")
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(hello_sdl hello_sdl.cpp)
add_executable(sdl_setup sdl_setup.cpp)
add_executable(game Game.cpp main.cpp)

set(SDL2_LIBRARIES "SDL2")
target_link_libraries(hello_sdl ${SDL2_LIBRARIES})
target_link_libraries(sdl_setup ${SDL2_LIBRARIES})
target_link_libraries(game ${SDL2_LIBRARIES})

