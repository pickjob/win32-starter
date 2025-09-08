project(demo_dll)

set(SOURCES
    main.c
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    common
)