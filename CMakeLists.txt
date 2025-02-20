cmake_minimum_required(VERSION 3.26)
project(GameTBD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "D:/C++/projects/sdl/SDL2-2.30.11/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "D:/C++/projects/sdl/SDL2_image-2.8.4/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "D:/C++/projects/sdl/SDL2_ttf-2.24.0/x86_64-w64-mingw32")

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

add_executable(GameTBD main.cpp
                Pacman.cpp
                Pacman.h
                Animation.cpp
                Animation.h)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
