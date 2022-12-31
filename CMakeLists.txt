cmake_minimum_required(VERSION 3.21.0)
project(win32-starter)

add_compile_definitions(UNICODE _UNICODE)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(utils)

add_subdirectory(0.hello_world)
add_subdirectory(1.show_case)
add_subdirectory(2.error_lookup)
