function(copy_file [target [src [dst]]])
    # Use POST_BUILD here so that CMake will have knowledge
    # of the project layout, targets, destinations, etc.
    add_custom_command(
        TARGET ${ARGV0} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${ARGV1}
        ${ARGV2}
    )
endfunction()

function(copy_directory [target [src [dst]]])
    # Use POST_BUILD here so that CMake will have knowledge
    # of the project layout, targets, destinations, etc.
    add_custom_command(
        TARGET ${ARGV0} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ARGV1}
        ${ARGV2}
    )
endfunction()
