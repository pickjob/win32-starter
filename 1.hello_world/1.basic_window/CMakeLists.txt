project(basic_window)

set(SOURCES
    main.c
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

# 内嵌 app.manifest
target_link_options(${PROJECT_NAME} PRIVATE
    /MANIFEST:EMBED
    "/MANIFESTINPUT:${CMAKE_CURRENT_SOURCE_DIR}/app.manifest"
)

target_link_libraries(${PROJECT_NAME}
    log
)