cmake_minimum_required(VERSION 3.15)
Project(game
        VERSION 0.0.1
        LANGUAGES CXX
        HOMEPAGE_URL "https://github.com/Kfeavel/SDL2-Game")

# Set project standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Set common locations
set(GAME_BIN_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(GAME_ASSET_DIR "${CMAKE_SOURCE_DIR}/assets/")

include(Utilities)

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

add_subdirectory("${CMAKE_SOURCE_DIR}/src")
