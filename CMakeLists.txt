cmake_minimum_required(VERSION 3.21.0)
project(win32-starter)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_definitions(UNICODE _UNICODE)

add_subdirectory(utils)

add_subdirectory(1.hello_world)
add_subdirectory(2.enum_resource)
add_subdirectory(3.show_case)

add_subdirectory(11.dll_inject)