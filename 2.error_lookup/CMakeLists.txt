project(error_lookup)

set(SOURCES
    main.c
    resource.rc
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    error_utils
    comctl32
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/app.manifest"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.exe.manifest"
)
