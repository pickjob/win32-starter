project(thread_show_case)

set(SOURCES
    main.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    error_utils
)
