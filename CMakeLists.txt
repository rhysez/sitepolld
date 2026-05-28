cmake_minimum_required(VERSION 4.2)
project(httphealthd C)

set(CMAKE_C_STANDARD 11)

add_executable(httphealthd src/main.c
        include/request.h
        src/request.c)

target_include_directories(httphealthd PRIVATE include)

target_link_libraries(httphealthd curl)
