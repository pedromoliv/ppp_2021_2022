cmake_minimum_required(VERSION 3.21)
project(Workspace_PPP C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Wextra)

add_executable(projeto source/main.c source/inc.h)