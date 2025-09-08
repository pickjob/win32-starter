project(common)

set(SOURCES
    common.c
)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

# 检查编译器是否为 Clang
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    # 添加 -fms-extensions 编译选项
    target_compile_options(${PROJECT_NAME} PRIVATE -fms-extensions)
endif()

target_link_libraries(${PROJECT_NAME}
    pthread
)