cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-fprofile-arcs -ftest-coverage")

add_compile_options(-Wall -Wextra -Werror)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g3 -gdwarf-4")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-4")

project(Chess)
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_subdirectory(program)
add_subdirectory(library)

enable_testing()