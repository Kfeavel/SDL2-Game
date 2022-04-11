cmake_minimum_required(VERSION 3.12)
Project(game_exe)

add_executable(game_exe
    main.cpp
)

target_compile_options(game_exe PRIVATE
    -Wall
    -Wextra
    -Werror
)

target_link_libraries(game_exe
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"
)

add_dependencies(game_exe copy_assets)
