cmake_minimum_required(VERSION 3.10)
Project(game_exe)

add_executable(game_exe
    main.cpp
)

target_link_libraries(game_exe
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)
