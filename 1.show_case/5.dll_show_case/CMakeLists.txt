project(dll_show_case)

set(SOURCES
    main.c
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    error_utils
)

add_subdirectory(inject)
