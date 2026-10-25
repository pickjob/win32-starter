cmake_minimum_required(VERSION 3.21.0)
project(win32-starter VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# MSVC 运行时库：动态 DLL 版本（/MD 或 /MDd）
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_compile_definitions(UNICODE _UNICODE)

add_compile_options(
    /W4                 # 高等级警告
    /utf-8              # 源码与执行字符集使用 UTF-8
    /MP                 # 多进程编译，加速构建
)

add_subdirectory(1.hello_world)
add_subdirectory(2.enum_resource)
add_subdirectory(3.show_case)

add_subdirectory(11.dll_inject)
add_subdirectory(12.pe_analyzer)

add_subdirectory(utils)