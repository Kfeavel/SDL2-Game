cmake_minimum_required(VERSION 3.15)
Project(game_exe
        VERSION 0.0.1
        LANGUAGES CXX)

add_executable(game_exe
    main.cpp
)

target_compile_options(game_exe PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

target_link_libraries(game_exe
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)

copy_directory(game_exe ${GAME_ASSET_DIR} ${GAME_BIN_DIR})
