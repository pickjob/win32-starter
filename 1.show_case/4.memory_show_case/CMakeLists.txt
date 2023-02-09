project(memory_show_case)

set(SOURCES
    main.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    error_utils
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/app.manifest"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.exe.manifest"
)
