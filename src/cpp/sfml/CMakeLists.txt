# Minimum required version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Project name and suppported language
project(sfml_test LANGUAGES CXX)

# Enable C++17 support
add_compile_options(-std=c++17)

if(WIN32)
    list(APPEND CMAKE_MODULE_PATH "D:/SW/SFML/cmake")
    include_directories("D:/SW/SFML/include")
    link_directories("D:/SW/SFML/build/lib")
else()
    # SFML library
    find_package(SFML REQUIRED graphics window system network audio)
    include_directories(${SFML_INCLUDE_DIR})
endif()

add_executable(window window.cpp)
add_executable(render render.cpp)
add_executable(shapes shapes.cpp)
add_executable(sfml_test sfml_test.cpp)
add_executable(shape_circle shape_circle.cpp)
add_executable(rand_gen rand_gen.cpp)
add_executable(game game.cpp)
add_executable(brick brick.cpp)
add_executable(square_game square_game.cpp)

target_link_libraries(window m sfml-graphics sfml-window sfml-system ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(render m sfml-graphics sfml-window sfml-system ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(shapes m sfml-graphics sfml-window sfml-system ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(sfml_test m sfml-graphics sfml-window sfml-system ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(shape_circle sfml-graphics sfml-window sfml-system ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(rand_gen sfml-graphics sfml-window sfml-system ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(game sfml-graphics sfml-window sfml-system sfml-audio ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(brick sfml-graphics sfml-window sfml-system sfml-audio ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(square_game sfml-graphics sfml-window sfml-system sfml-audio ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
